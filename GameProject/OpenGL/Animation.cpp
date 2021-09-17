/*
@file  Animation.h
@brief Skeleton��p�����A�j���[�V�����̃f�[�^�N���X
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn    �A�j���[�V�����ǂݍ���
@param �A�j���[�V�����ւ̃p�X
*/
bool Animation::Load(const std::string& _FileName)
{
	// filename����e�L�X�g�t�@�C���Ƃ��ēǂݍ��݁ArapidJSON�ɉ�͂�����
	std::ifstream file(_FileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Animation %s", _FileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	// JSON�I�u�W�F�N�g���H
	if (!doc.IsObject())
	{
		SDL_Log("Animation %s is not valid json", _FileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata�@���^�f�[�^�̃`�F�b�N�B�o�[�W�����͂P���H
	if (ver != 1)
	{
		SDL_Log("Animation %s unknown format", _FileName.c_str());
		return false;
	}

	// "sequece"���ǂݍ��߂邩�H
	const rapidjson::Value& Sequence = doc["sequence"];
	if (!Sequence.IsObject())
	{
		SDL_Log("Animation %s doesn't have a sequence.", _FileName.c_str());
		return false;
	}

	// "frames" "length" "bonecount"�͂��邩�H
	const rapidjson::Value& Fames = Sequence["frames"];
	const rapidjson::Value& Length = Sequence["length"];
	const rapidjson::Value& Bonecount = Sequence["bonecount"];

	if (!Fames.IsUint() || !Length.IsDouble() || !Bonecount.IsUint())
	{
		SDL_Log("Sequence %s has invalid frames, length, or bone count.", _FileName.c_str());
		return false;
	}

	// �t���[�����A�A�j���[�V�������ԁA�{�[�����A�t���[��������̎��Ԃ��擾
	mNumFrames = Fames.GetUint();
	mDuration = static_cast<float>(Length.GetDouble());
	mNumBones = Bonecount.GetUint();
	mFrameDuration = mDuration / (mNumFrames - 1);

	// �g���b�N�z����m��
	mTracks.resize(mNumBones);

	// �g���b�N�z�񂪎擾�ł��邩�H
	const rapidjson::Value& Tracks = Sequence["tracks"];

	if (!Tracks.IsArray())
	{
		SDL_Log("Sequence %s missing a tracks array.", _FileName.c_str());
		return false;
	}

	// �g���b�N�������[�v
	for (rapidjson::SizeType i = 0; i < Tracks.Size(); i++)
	{
		// tracs[i]�̓I�u�W�F�N�g���H
		if (!Tracks[i].IsObject())
		{
			SDL_Log("Animation %s: Track element %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// tracks[i]�̒��� "bone"��uint�œǂݍ��݁B�{�[���ԍ����擾
		size_t boneIndex = Tracks[i]["bone"].GetUint();
		
		// tracks[i]�̒��� "transforms"���擾�ł��邩�H
		const rapidjson::Value& Transforms = Tracks[i]["transforms"];
		if (!Transforms.IsArray())
		{
			SDL_Log("Animation %s: Track element %d is missing transforms.", _FileName.c_str(), i);
			return false;
		}

		BoneTransform temp;
		// transform�̃T�C�Y�ƃA�j���[�V�����t���[�������s��Ȃ����H
		if (Transforms.Size() < mNumFrames)
		{
			SDL_Log("Animation %s: Track element %d has fewer frames than expected.", _FileName.c_str(), i);
			return false;
		}

		// transforms�̃T�C�Y�����[�v�B�{�[���ԍ�boneIndex�̕ϊ����Ƃ��Ď�荞��
		for (rapidjson::SizeType j = 0; j < Transforms.Size(); j++)
		{
			// ���[�e�[�V����(quaternion)��trans(���s�ړ�����)��ǂݍ���
			const rapidjson::Value& Rot = Transforms[j]["rot"];
			const rapidjson::Value& Trans = Transforms[j]["trans"];

			if (!Rot.IsArray() || !Trans.IsArray())
			{
				SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
				return false;
			}

			// temp.mRotation�Ɂ@quaternion�Ƃ��ăR�s�[�A
			temp.mRotation.x = static_cast<float>(Rot[0].GetDouble());
			temp.mRotation.y = static_cast<float>(Rot[1].GetDouble());
			temp.mRotation.z = static_cast<float>(Rot[2].GetDouble());
			temp.mRotation.w = static_cast<float>(Rot[3].GetDouble());

			// temp.mTranslation�ɕ��s�ړ������Ƃ��ăR�s�[
			temp.mTranslation.x = static_cast<float>(Trans[0].GetDouble());
			temp.mTranslation.y = static_cast<float>(Trans[1].GetDouble());
			temp.mTranslation.z = static_cast<float>(Trans[2].GetDouble());

			// �{�[���ԍ�boneIndex�̎p���f�[�^�Ƃ��āAmTracks�z��ɓ����B
			mTracks[boneIndex].emplace_back(temp);
		}
	}

	return true;
}

// inTime�������_�̃O���[�o���|�[�Y�z��̎擾
void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& _outPoses, const Skeleton* _InSkeleton, float _inTime) const
{
	if (_outPoses.size() != mNumBones)
	{
		_outPoses.resize(mNumBones);
	}

	// Figure out the current frame index and next frame
	// (This assumes inTime is bounded by [0, AnimDuration]
	// ���݂̃t���[���Ǝ��̃t���[���������o���B
	// �����inTime�� [0�`AnimDuration] �̊Ԃɂ��邱�Ƃ�O��Ƃ��Ă��܂��B
	size_t frame = static_cast<size_t>(_inTime / mFrameDuration);
	size_t nextFrame = frame + 1;
	// Calculate fractional value between frame and next frame
	// �t���[���Ǝ��̃t���[���̊Ԃ̏����l���v�Z���܂��B
	float pct = _inTime / mFrameDuration - frame;

	// Setup the pose for the root
	// ���[�g�̃|�[�Y���Z�b�g�A�b�v
	if (mTracks[0].size() > 0)
	{
		// Interpolate between the current frame's pose and the next frame
		// ���݂̃t���[���̃|�[�Y�Ǝ��̃t���[���̊Ԃ��Ԃ���
		BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame],
			mTracks[0][nextFrame], pct);
		_outPoses[0] = interp.ToMatrix();
	}
	else
	{
		_outPoses[0] = Matrix4::sIDENTITY;
	}

	const std::vector<Skeleton::Bone>& Bones = _InSkeleton->GetBones();
	// Now setup the poses for the rest
	// �c��̃|�[�Y��ݒ肵�܂�
	for (size_t bone = 1; bone < mNumBones; bone++)
	{
		Matrix4 localMat; // (Defaults to identity)�@�i�f�t�H���g�͒P�ʍs��j
		if (mTracks[bone].size() > 0)
		{
			// [bone][frame]�̃{�[���p����[bone][nextframe]�� �����_�ȉ��� pct�ŕ�Ԃ����p���� interp�ɎZ�o
			BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
				mTracks[bone][nextFrame], pct);
			// interp ���s��ɕϊ����āAlocalMat�ɕϊ�����
			localMat = interp.ToMatrix();
		}

		// �o�̓|�[�Y�s��[bone] = ���[�J���|�[�Y�s�� * �o�̓|�[�Y�s��[�ebone]
		_outPoses[bone] = localMat * _outPoses[Bones[bone].mParent];
	}
}
