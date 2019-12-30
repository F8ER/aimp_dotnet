// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceThreadPool.h"
#include "InternalAimpTask.h"

using namespace AIMP::SDK;

AimpServiceThreadPool::AimpServiceThreadPool(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceThreadPool>(core)
{
}

AimpActionResult AimpServiceThreadPool::Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags)
{
    IAIMPServiceThreadPool* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            return CheckResult(service->Cancel(DWORD_PTR(taskHandle.ToPointer()), DWORD(flags)));
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return AimpActionResult::Fail;
}

AimpActionResult AimpServiceThreadPool::Execute(IAimpTask^ task, UIntPtr% handle)
{
    IAIMPServiceThreadPool* service = GetAimpService();
    handle = UIntPtr(static_cast<void*>(0));

    try
    {
        DWORD_PTR h;

        if (service != nullptr)
        {
            InternalAimpTask* internalTask = new InternalAimpTask(task);
            AimpActionResult result = CheckResult(service->Execute(internalTask, &h));
            handle = UIntPtr(reinterpret_cast<void*>(h));
            return result;
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return AimpActionResult::Fail;
}

AimpActionResult AimpServiceThreadPool::WaitFor(UIntPtr handle)
{
    IAIMPServiceThreadPool* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            return CheckResult(service->WaitFor(reinterpret_cast<DWORD_PTR>(handle.ToPointer())));
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return AimpActionResult::Fail;
}

IAIMPServiceThreadPool* AimpServiceThreadPool::GetAimpService()
{
    IAIMPServiceThreadPool* service = nullptr;
    GetService(IID_IAIMPServiceThreadPool, &service);
    return service;
}
