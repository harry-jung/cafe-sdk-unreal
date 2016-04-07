#pragma once

#if PLATFORM_ANDROID

#include "Core.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#include "Runtime/Launch/Public/Android/AndroidJNI.h"

class FAndroidJavaGlink
{
public:
    FAndroidJavaGlink();
    
    void Init(FString ClientId, FString ClientSecret, int32 CafeId) const;
    
    void StartHome() const;
    void StartNotice() const;
    void StartEvent() const;
    void StartMenu() const;
    void StartMenuById(int32 MenuId) const;
    void StartProfile() const;
    
    bool IsShow() const;
    void SyncGameUserId(FString GameUserId) const;
    
private:
    static FName GetClassName();
    
    FJavaClassMethod GetClassStaticMethod(const char* MethodName, const char* FuncSig) const;
    
    void StartTab(const FJavaClassMethod& JavaClassMethod) const;
    
    jclass Class;
    FJavaClassMethod InitMethod;
    FJavaClassMethod StartHomeMethod;
    FJavaClassMethod StartNoticeMethod;
    FJavaClassMethod StartEventMethod;
    FJavaClassMethod StartMenuMethod;
    FJavaClassMethod StartMenuByIdMethod;
    FJavaClassMethod StartProfileMethod;
    FJavaClassMethod IsShowMethod;
    FJavaClassMethod SyncGameUserIdMethod;
};

#endif // PLATFORM_ANDROID