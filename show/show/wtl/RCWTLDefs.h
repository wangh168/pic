/******************************************************************************
 *  版权所有（C）2013-2015，上海二三四五网络科技有限公司                      *
 *  保留所有权利。                                                            *
 ******************************************************************************
 *  作者 : 李春志
 *  版本 : 1.0
 *****************************************************************************/

#ifndef __RCWTLDefs_h_
#define __RCWTLDefs_h_ 1

#include "base/RCDefs.h"
#include <shellapi.h>   // atlctrlx.h -- CHyperLinkImpl

/** RichEdit 控件版本定义
*/
#undef  _RICHEDIT_VER
#define _RICHEDIT_VER 0x0200

#include <objidl.h>
#include <commctrl.h>
#include <algorithm>
using std::max;
using std::min;

#define _SECURE_ATL 1
#define _ATL_NO_COM 1

#include <atlbase.h>
#include "wtl/atlapp.h"
#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>
#include <atlcoll.h>

#ifdef _WTL_USE_CSTRING
    #undef _WTL_USE_CSTRING
#endif

#ifdef __ATLSTR_H__
    #undef __ATLSTR_H__
#endif

#include "wtl/atlframe.h"
#include "wtl/atlctrls.h"
#include "wtl/atlctrlx.h"
#include "wtl/atldlgs.h"
#include "wtl/atlctrlw.h"
#include "wtl/atlcrack.h"
#include "wtl/atlmisc.h"
#include "wtl/atlddx.h"
#include "wtl/atlgdi.h"

#endif //__RCWTLDefs_h_
