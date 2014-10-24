#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_XML_MANAGER_C_BIND_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_XML_MANAGER_C_BIND_H

#include "XmlManager.h"
#include <linux/types.h>



extern "C"
{

void XmlManagerSaveCode (char *, const __s32, const __u64);

}// extern "C"

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_XML_MANAGER_C_BIND_H
