// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\AimpObject.h"
#include "SDK\ManagedAimpCore.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace FileManager;

        public ref class AimpVirtualFile : public AimpObject<IAIMPVirtualFile>, public IAimpVirtualFile {
        public:
            AimpVirtualFile(IAIMPVirtualFile* aimpObject);

            virtual property int IndexInSet
            {
                int get();
                void set(int value);
            }

            virtual property double ClipStart
            {
                double get();
                void set(double value);
            }

            virtual property double ClipFinish
            {
                double get();
                void set(double value);
            }

            virtual property String^ AudioSourceFile
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ FileFormat
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ FileUri
            {
                String^ get();
                void set(String^ value);
            }

            virtual StreamResult CreateStream();

            virtual FileInfoResult GetFileInfo();

            virtual bool IsExists();

            virtual ActionResult IsInSameStream(IAimpVirtualFile^ virtualFile);

            virtual ActionResult Synchronize();
        };
    }
}
