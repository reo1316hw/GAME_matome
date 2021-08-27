//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "pch.h"

#include "Windows.h"

/*
クラス内での宣言順番はpublic>protected>private>public(GetSet)の順
*/

/*
 @file 名.h
 @brief 簡単な説明
*/

/*
   @fn ここに関数の説明を書く
   @brief 要約説明
   @param 引数名 説明
   @return 戻り値の説明
   @sa 参照すべき関数を書けばリンクが貼れる
   @detail 詳細な説明
 */

/*
	@param 引数名 説明
*/

/*
  @fn
  @brief
*/

/*
  @fn
*/

/*
   @fn
   @brief
   @return
*/

/*
	 @enum Enum
	 説明
*/

///*
//@fn		ランチャー(Launcher.exe)呼び出し関数 
//@param	_path Launcher.exeへの相対パスへの文字列を入れる
//*/
//void runLauncher(const char* _path)
//{
//
//	char fullPathexe[512];
//#pragma warning (disable:4996)
//	sprintf(fullPathexe, "%s%s", _path, "Launcher.exe");
//
//	// プロセス起動準備
//	PROCESS_INFORMATION pi = { 0 };
//	STARTUPINFO si = { 0 };
//	si.cb = sizeof(STARTUPINFO);
//
//	CreateProcess(fullPathexe, (LPSTR)"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, _path, &si, &pi);
//}


/*
@fn		main関数
@param  argc コマンドライン引数の数
@param  argv コマンドライン引数
*/
int main(int argc, char** argv)
{
	//ゲームクラスの定義
	Game game;
	//ゲームクラスの初期化が成功したか
	bool success = game.Initialize();
	game.SetFirstScene(new TitleScene(SceneBase::title));
	if (success)
	{
		game.GameLoop();
	}
	//ゲームクラスの終了処理
	game.Termination();

	//runLauncher("../../");

	return 0;
}