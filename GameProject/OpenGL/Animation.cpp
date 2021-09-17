/*
@file  Animation.h
@brief Skeletonを用いたアニメーションのデータクラス
*/

/*
@brief インクルード
*/
#include "pch.h"

/*
@fn    アニメーション読み込み
@param アニメーションへのパス
*/
bool Animation::Load(const std::string& _FileName)
{
	// filenameからテキストファイルとして読み込み、rapidJSONに解析させる
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

	// JSONオブジェクトか？
	if (!doc.IsObject())
	{
		SDL_Log("Animation %s is not valid json", _FileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata　メタデータのチェック。バージョンは１か？
	if (ver != 1)
	{
		SDL_Log("Animation %s unknown format", _FileName.c_str());
		return false;
	}

	// "sequece"情報読み込めるか？
	const rapidjson::Value& Sequence = doc["sequence"];
	if (!Sequence.IsObject())
	{
		SDL_Log("Animation %s doesn't have a sequence.", _FileName.c_str());
		return false;
	}

	// "frames" "length" "bonecount"はあるか？
	const rapidjson::Value& Fames = Sequence["frames"];
	const rapidjson::Value& Length = Sequence["length"];
	const rapidjson::Value& Bonecount = Sequence["bonecount"];

	if (!Fames.IsUint() || !Length.IsDouble() || !Bonecount.IsUint())
	{
		SDL_Log("Sequence %s has invalid frames, length, or bone count.", _FileName.c_str());
		return false;
	}

	// フレーム数、アニメーション時間、ボーン数、フレームあたりの時間を取得
	mNumFrames = Fames.GetUint();
	mDuration = static_cast<float>(Length.GetDouble());
	mNumBones = Bonecount.GetUint();
	mFrameDuration = mDuration / (mNumFrames - 1);

	// トラック配列を確保
	mTracks.resize(mNumBones);

	// トラック配列が取得できるか？
	const rapidjson::Value& Tracks = Sequence["tracks"];

	if (!Tracks.IsArray())
	{
		SDL_Log("Sequence %s missing a tracks array.", _FileName.c_str());
		return false;
	}

	// トラック数分ループ
	for (rapidjson::SizeType i = 0; i < Tracks.Size(); i++)
	{
		// tracs[i]はオブジェクトか？
		if (!Tracks[i].IsObject())
		{
			SDL_Log("Animation %s: Track element %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// tracks[i]の中の "bone"をuintで読み込み。ボーン番号を取得
		size_t boneIndex = Tracks[i]["bone"].GetUint();
		
		// tracks[i]の中の "transforms"が取得できるか？
		const rapidjson::Value& Transforms = Tracks[i]["transforms"];
		if (!Transforms.IsArray())
		{
			SDL_Log("Animation %s: Track element %d is missing transforms.", _FileName.c_str(), i);
			return false;
		}

		BoneTransform temp;
		// transformのサイズとアニメーションフレーム数が不具合ないか？
		if (Transforms.Size() < mNumFrames)
		{
			SDL_Log("Animation %s: Track element %d has fewer frames than expected.", _FileName.c_str(), i);
			return false;
		}

		// transformsのサイズ分ループ。ボーン番号boneIndexの変換情報として取り込む
		for (rapidjson::SizeType j = 0; j < Transforms.Size(); j++)
		{
			// ローテーション(quaternion)とtrans(平行移動成分)を読み込む
			const rapidjson::Value& Rot = Transforms[j]["rot"];
			const rapidjson::Value& Trans = Transforms[j]["trans"];

			if (!Rot.IsArray() || !Trans.IsArray())
			{
				SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
				return false;
			}

			// temp.mRotationに　quaternionとしてコピー、
			temp.mRotation.x = static_cast<float>(Rot[0].GetDouble());
			temp.mRotation.y = static_cast<float>(Rot[1].GetDouble());
			temp.mRotation.z = static_cast<float>(Rot[2].GetDouble());
			temp.mRotation.w = static_cast<float>(Rot[3].GetDouble());

			// temp.mTranslationに平行移動成分としてコピー
			temp.mTranslation.x = static_cast<float>(Trans[0].GetDouble());
			temp.mTranslation.y = static_cast<float>(Trans[1].GetDouble());
			temp.mTranslation.z = static_cast<float>(Trans[2].GetDouble());

			// ボーン番号boneIndexの姿勢データとして、mTracks配列に入れる。
			mTracks[boneIndex].emplace_back(temp);
		}
	}

	return true;
}

// inTime時刻時点のグローバルポーズ配列の取得
void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& _outPoses, const Skeleton* _InSkeleton, float _inTime) const
{
	if (_outPoses.size() != mNumBones)
	{
		_outPoses.resize(mNumBones);
	}

	// Figure out the current frame index and next frame
	// (This assumes inTime is bounded by [0, AnimDuration]
	// 現在のフレームと次のフレームを見つけ出す。
	// これはinTimeが [0～AnimDuration] の間にいることを前提としています。
	size_t frame = static_cast<size_t>(_inTime / mFrameDuration);
	size_t nextFrame = frame + 1;
	// Calculate fractional value between frame and next frame
	// フレームと次のフレームの間の小数値を計算します。
	float pct = _inTime / mFrameDuration - frame;

	// Setup the pose for the root
	// ルートのポーズをセットアップ
	if (mTracks[0].size() > 0)
	{
		// Interpolate between the current frame's pose and the next frame
		// 現在のフレームのポーズと次のフレームの間を補間する
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
	// 残りのポーズを設定します
	for (size_t bone = 1; bone < mNumBones; bone++)
	{
		Matrix4 localMat; // (Defaults to identity)　（デフォルトは単位行列）
		if (mTracks[bone].size() > 0)
		{
			// [bone][frame]のボーン姿勢と[bone][nextframe]を 小数点以下の pctで補間した姿勢を interpに算出
			BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
				mTracks[bone][nextFrame], pct);
			// interp を行列に変換して、localMatに変換する
			localMat = interp.ToMatrix();
		}

		// 出力ポーズ行列[bone] = ローカルポーズ行列 * 出力ポーズ行列[親bone]
		_outPoses[bone] = localMat * _outPoses[Bones[bone].mParent];
	}
}
