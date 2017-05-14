/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once
#include "Stdafx.h"
#include "AimpActionManager.h"
#include "AimpAction.h"

namespace AIMP
{
    namespace SDK
    {
        AimpActionManager::AimpActionManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceActionManager>(core)
        { }

        AimpActionManager::~AimpActionManager()
        {
            System::Diagnostics::Debug::WriteLine("Dispose AimpActionManager");
        }

        AimpActionResult AimpActionManager::GetById(String ^id, IAimpAction ^%action)
        {
            AimpActionResult result = AimpActionResult::Fail;
            IAIMPServiceActionManager *service = NULL;

            try
            {
                if (GetService(IID_IAIMPServiceActionManager, &service) == AimpActionResult::Ok)
                {
                    if (service != NULL)
                    {
                        IAIMPAction *resAction;
                        IAIMPString *strId = AimpConverter::ToAimpString(id);
                        result = CheckResult(service->GetByID(strId, &resAction));
                        if (result == AimpActionResult::Ok)
                        {
                            action = gcnew AimpAction(resAction);
                        }
                        strId->Release();
                    }
                }

                return result;
            }
            finally
            {
                if (service != NULL)
                {
                    service->Release();
                    service = NULL;
                }
            }
        }

        int AimpActionManager::MakeHotkey(ModifierKeys modifiers, unsigned int key)
        {
            IAIMPServiceActionManager *service = NULL;

            try
            {
                if (GetService(IID_IAIMPServiceActionManager, &service) == AimpActionResult::Ok)
                {
                    if (service != NULL)
                    {
                        return service->MakeHotkey((DWORD)modifiers, key);
                    }
                }
            }
            finally
            {
                if (service != NULL)
                {
                    service->Release();
                    service = NULL;
                }
            }

            return 0;
        }

        AimpActionResult AimpActionManager::Register(IAimpAction ^action)
        {
            return CheckResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceActionManager, ((AimpAction^)action)->InternalAimpObject));
        }

        AimpActionResult AimpActionManager::Register(System::Collections::Generic::ICollection<IAimpAction^>^ actions)
        {
            AimpActionResult result = AimpActionResult::Fail;

            for each(AimpActionItem^ item in actions)
            {
                result = Register(item);

                if (result != AimpActionResult::Ok)
                {
                    return result;
                }
            }

            return result;
        }
    }
}
