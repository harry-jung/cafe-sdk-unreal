// Copyright 2016 NAVER Corp. All rights reserved.

#pragma once

#include "Core.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#include "Runtime/Launch/Public/Android/AndroidJNI.h"

class FAndroidJavaGlink
{
public:
    FAndroidJavaGlink();
    
    void StartHome() const;
    void StartNotice() const;
    void StartEvent() const;
    void StartMenu() const;
    void StartMenuById(int32 MenuId) const;
    void StartProfile() const;
    void StartWrite(int32 MenuId, FString Subject, FString Text) const;
    void StartImageWrite(int32 MenuId, FString Subject, FString Text, FString ImageUri) const;
    void StartVideoWrite(int32 MenuId, FString Subject, FString Text, FString VideoUri) const;
    
    bool IsShow() const;
    void SyncGameUserId(FString GameUserId) const;
    
    void ShowWidgetWhenUnloadSdk(bool bUse) const;
    void StopWidget() const;
    void SetUseVideoRecord(bool bUse) const;
    void SetThemeColor(FString ThemeColorCSSString, FString TabBackgroundColorCSSString) const;
    void SetXButtonTypeClose(bool bUse) const;
    
    bool IsSupportedAndroidVersion() const;
    
private:
    static FName GetClassName();
    
    FJavaClassMethod GetClassStaticMethod(const char* MethodName, const char* FuncSig) const;
    
    void StartTab(const FJavaClassMethod& JavaClassMethod) const;
    
    jclass Class;
    FJavaClassMethod StartHomeMethod;
    FJavaClassMethod StartNoticeMethod;
    FJavaClassMethod StartEventMethod;
    FJavaClassMethod StartMenuMethod;
    FJavaClassMethod StartMenuByIdMethod;
    FJavaClassMethod StartProfileMethod;
    FJavaClassMethod StartWriteMethod;
    FJavaClassMethod StartImageWriteMethod;
    FJavaClassMethod StartVideoWriteMethod;
    FJavaClassMethod SetThemeColorMethod;
    FJavaClassMethod SetXButtonTypeCloseMethod;
    FJavaClassMethod IsShowMethod;
    FJavaClassMethod SyncGameUserIdMethod;
    FJavaClassMethod ShowWidgetWhenUnloadSdkMethod;
    FJavaClassMethod StopWidgetMethod;
    FJavaClassMethod SetUseVideoRecordMethod;
    FJavaClassMethod GetAndroidVersionMethod;
};

FAndroidJavaGlink* GetSharedGlink();
