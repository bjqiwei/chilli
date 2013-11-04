#ifndef _PUTTEXTINPICTURE_H
#define _PUTTEXTINPICTURE_H

#ifdef __cplusplus
extern "C"
{
#endif

#define PUTTEXTINPICTURE_EXPORTS

#ifdef _WIN32
	#ifdef PUTTEXTINPICTURE_EXPORTS
	#define PUTTEXTINPICTURE_API __declspec(dllexport)
	#else
	#define PUTTEXTINPICTURE_API __declspec(dllimport)
	#endif
#else
	#define PUTTEXTINPICTURE_API
void so_init(void) __attribute__((constructor)); // init section
void so_fini(void) __attribute__((destructor));  // fini section
#endif

enum tagFontType	/* .\\PutTextInPicture.ini */
{
	FONTTYPE_simsun = 0,				// 宋体&新宋体
		FONTTYPE_micross				// Microsoft Sans Serif
};

typedef unsigned char byte;
enum tagType
{
	Type_Text = 1,
		Type_Picture = 2
};
typedef struct tagPutTextInPictureParamItem
{
	byte byType;		// 1-文字 2-图片
	byte byLevel;		// 图层
	char chText[260];	// 文字串
	WORD wFontType;		// 字体类型
	struct tagDllFONTPARAM
	{
		double dbSize;		// 字体大小 默认可设置20.0
		double dbBlank;		// 空白比例 默认可设置0.5
		double dbGap;		// 间隔比例 默认可设置0.1
		double dbAngle;		// 旋转角度(不支持)
		bool bUnderLine;	// 是否下划线(不支持)
		struct tagDllCOLOR
		{
			byte byR;
			byte byG;
			byte byB;
		} strcutColor;		// 字体颜色
	} structFontParam;
	float fDiaphaneity;	// 透明度 默认可设置1.0不透明
	struct tagDllPOINT
	{
		int x;
		int y;
	} structPoint;		// 文字图片的位置或背景图片的宽高
}PUTTEXTINPICTUREPARAMITEM, *LPPUTTEXTINPICTUREPARAMITEM;

/*
* 目前仅支持：paramItem参数
* 第一个成员必须为图片(图片地址若为""则为无底图且大小可以由structPoint指定) 自动置为第一层
* byLevel无需填写 文字自动在第二层
* 文字只支持中英文 支持其他文字可自定义ini文件并将字体文件放入Fonts文件夹
* 图片格式由图片后缀名决定
*/

/*
* chDstFile 输出文件
* paramItem PUTTEXTINPICTUREPARAMITEM[iParamSum]
* return tagPutTextInPictureResult
*/
enum tagPutTextInPictureResult
{
	PutTextInPictureResult_Success = 0,					// 成功
		PutTextInPictureResult_ParamError = 1,			// 参数错误
		PutTextInPictureResult_OpenPicError = 2,		// 打开文件失败
		PutTextInPictureResult_SavePicError = 3			// 保存文件失败
};
PUTTEXTINPICTURE_API int PutTextInPicture(char *chDstFile, PUTTEXTINPICTUREPARAMITEM *paramItem, int iParamSum);


#ifdef __cplusplus
}
#endif

#endif
