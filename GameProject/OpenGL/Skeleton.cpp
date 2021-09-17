/*
@file  Skeleton.h
@brief ���i
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn �X�P���g���̃t�@�C������̃��[�h
@param _FileName
@return �����A���s
*/
bool Skeleton::Load(const std::string& _FileName)
{
	// �t�@�C��������e�L�X�g�t�@�C�����I�[�v�����āARapidJSON�ɉ�͂�����
	std::ifstream file(_FileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Skeleton %s", _FileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	// JSON�I�u�W�F�N�g��
	if (!doc.IsObject())
	{
		SDL_Log("Skeleton %s is not valid json", _FileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata�@���^�f�[�^�̃`�F�b�N�i�o�[�W�����`�F�b�N�j
	if (ver != 1)
	{
		SDL_Log("Skeleton %s unknown format", _FileName.c_str());
		return false;
	}

	// bonecount �{�[�����̎擾
	const rapidjson::Value& Bonecount = doc["bonecount"];
	if (!Bonecount.IsUint())
	{
		SDL_Log("Skeleton %s doesn't have a bone count.", _FileName.c_str());
		return false;
	}

	size_t count = Bonecount.GetUint();

	// �{�[������MAX_SKELETON_BONES�𒴂��Ă����ꍇ (196�{���ő�)
	if (count > MAX_SKELETON_BONES)
	{
		SDL_Log("Skeleton %s exceeds maximum bone count.", _FileName.c_str());
		return false;
	}

	mBones.reserve(count);

	// �{�[���z��̎擾
	const rapidjson::Value& Bones = doc["bones"];
	if (!Bones.IsArray())
	{
		SDL_Log("Skeleton %s doesn't have a bone array?", _FileName.c_str());
		return false;
	}

	// �{�[���z��̃T�C�Y�ƃ{�[�������قȂ�ꍇ�̓G���[��Ԃ�
	if (Bones.Size() != count)
	{
		SDL_Log("Skeleton %s has a mismatch between the bone count and number of bones", _FileName.c_str());
		return false;
	}

	Bone temp;

	// �{�[���z�񐔕����[�v
	for (rapidjson::SizeType i = 0; i < count; i++)
	{
		// �{�[�����ǂ߂邩�H
		if (!Bones[i].IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// "name" �{�[����
		const rapidjson::Value& Name = Bones[i]["name"];
		temp.mName = Name.GetString();

		// "parent" �e�{�[��ID
		const rapidjson::Value& Parent = Bones[i]["parent"];
		temp.mParent = Parent.GetInt();

		// "bindpose" �o�C���h�|�[�Y
		const rapidjson::Value& Bindpose = Bones[i]["bindpose"];
		if (!Bindpose.IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// �o�C���h�|�[�Y�̉�]�A�ʒu
		const rapidjson::Value& Rot = Bindpose["rot"];
		const rapidjson::Value& Trans = Bindpose["trans"];

		// ��]�ƈʒu���z�񂶂�Ȃ�������G���[�Ԃ�
		if (!Rot.IsArray() || !Trans.IsArray())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// �o�C���h�|�[�Y�̉�]����
		temp.mLocalBindPose.mRotation.x = static_cast<float>(Rot[0].GetDouble());
		temp.mLocalBindPose.mRotation.y = static_cast<float>(Rot[1].GetDouble());
		temp.mLocalBindPose.mRotation.z = static_cast<float>(Rot[2].GetDouble());
		temp.mLocalBindPose.mRotation.w = static_cast<float>(Rot[3].GetDouble());

		// �o�C���h�|�[�Y�̈ړ�����
		temp.mLocalBindPose.mTranslation.x = static_cast<float>(Trans[0].GetDouble());
		temp.mLocalBindPose.mTranslation.y = static_cast<float>(Trans[1].GetDouble());
		temp.mLocalBindPose.mTranslation.z = static_cast<float>(Trans[2].GetDouble());

		// �{�[���z��Ɋi�[����
		mBones.emplace_back(temp);
	}

	// Now that we have the bones�@�����Ń{�[���z��͓ǂ݂��܂�Ă���̂ŁA�t�o�C���h�|�[�Y�s����v�Z����
	ComputeGlobalInvBindPose();

	return true;
}

/*
@fn �X�P���g�������[�h���ꂽ�Ƃ��Ɏ����I�ɌĂяo����e�{�[���̃O���[�o���t�o�C���h�|�[�Y���v�Z
*/
void Skeleton::ComputeGlobalInvBindPose()
{
	// Resize to number of bones, which automatically fills identity    mGlobalInvIndPoses�z����A�{�[�������m�ہ������I�ɒP�ʍs��ŏ�����
	mGlobalInvBindPoses.resize(GetNumBones());

	// Step 1: Compute global bind pose for each bone�@�@�@�@�@�@�@�@�@�@�@�X�e�b�v�P�F���ꂼ��̃{�[���̃O���[�o���o�C���h�|�[�Y���v�Z

	// The global bind pose for root is just the local bind pose         root ([0]�̂���) �̃O���[�o���o�C���h�|�[�Y�́A���[�J���o�C���h�|�[�Y�̂��Ƃł��B
	mGlobalInvBindPoses[0] = mBones[0].mLocalBindPose.ToMatrix();

	// Each remaining bone's global bind pose is its local pose          �c��̊e�{�[���̃O���[�o���o�C���h�|�[�Y�́A
	// multiplied by the parent's global bind pose                       ���̃��[�J���|�[�Y�ɐe�̃O���[�o���o�C���h�|�[�Y���|�������̂ł��B
	for (size_t i = 1; i < mGlobalInvBindPoses.size(); i++)
	{
		Matrix4 localMat = mBones[i].mLocalBindPose.ToMatrix();                     // ���̃{�[���̃��[�J���o�C���h�|�[�Y���s��ɕϊ����� locakMat�ɑ��
		mGlobalInvBindPoses[i] = localMat * mGlobalInvBindPoses[mBones[i].mParent]; // localMat * �����̐e�̃O���[�o���o�C���h�|�[�Y�s��
	}

	// Step 2: Invert                                                   �X�e�b�v�Q�F�t�s��ɂ���
	for (size_t i = 0; i < mGlobalInvBindPoses.size(); i++)
	{
		mGlobalInvBindPoses[i].Invert();
	}
}
