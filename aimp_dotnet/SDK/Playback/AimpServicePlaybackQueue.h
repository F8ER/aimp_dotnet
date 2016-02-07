#pragma once

#include "..\BaseManager.h"
#include "AimpPlaybackQueueItem.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::PlayList;
        using namespace AIMP::SDK::Playback;

        public ref class AimpServicePlaybackQueue : public AimpBaseManager<IAIMPServicePlaybackQueue>, public IAimpPlaybackQueueService
        {
        private:
            AimpCheckUrl ^_checkUrlHandler;

        public:
            explicit AimpServicePlaybackQueue(ManagedAimpCore ^core) : AimpBaseManager<IAIMPServicePlaybackQueue>(core)
            {
            }

            ~AimpServicePlaybackQueue()
            {
            }

            virtual IAimpPlaybackQueueItem^ GetNextTrack()
            {
                IAIMPPlaybackQueueItem *item = NULL;
                IAIMPServicePlaybackQueue *service = NULL;
                try
                {
                    if (CheckResult(_core->GetService(IID_IAIMPServicePlaybackQueue, (void**)&service)) == AimpActionResult::Ok)
                    {
                        if (CheckResult(service->GetNextTrack(&item)) == AimpActionResult::Ok)
                        {
                            return gcnew AimpPlaybackQueueItem(item);
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

                    if (item != NULL)
                    {
                        item->Release();
                        item = NULL;
                    }
                }

                return nullptr;
            }

            virtual IAimpPlaybackQueueItem^ GetPrevTrack()
            {
                IAIMPPlaybackQueueItem *item = NULL;
                IAIMPServicePlaybackQueue *service = NULL;

                try
                {
                    if (CheckResult(service->GetPrevTrack(&item)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlaybackQueueItem(item);
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }

                    if (item != NULL)
                    {
                        item->Release();
                        item = NULL;
                    }
                }
                
                return nullptr;
            }

            virtual event AimpCheckUrl ^OnCheckURL
            {
                void add(AimpCheckUrl ^onEvent)
                {
                    bool tmp = _checkUrlHandler == nullptr;
                    if (tmp)
                    {
                        _checkUrlHandler = (AimpCheckUrl^)System::Delegate::Combine(_checkUrlHandler, onEvent);
                    }
                }

                void remove(AimpCheckUrl ^onEvent)
                {
                    bool tmp = _checkUrlHandler != nullptr;
                    if (tmp)
                    {
                        _checkUrlHandler = (AimpCheckUrl^)System::Delegate::Remove(_checkUrlHandler, onEvent);
                    }
                }
            }
        internal:
            bool RaiseCheckUrl(String^ %url)
            {
                bool tmp = this->_checkUrlHandler != nullptr;
                if (tmp)
                {
                    return _checkUrlHandler(url);
                }
            }
        };
    }
}