// Copyright 2016 NAVER Corp. All rights reserved.

#include "CafeSDKPluginPrivatePCH.h"
#include "IOSAppDelegate.h"
#include "IOSPlatformString.h"

FIOSCafeSdk* GetSharedCafeSdk()
{
    static FIOSCafeSdk* CafeSdk = nullptr;
    if (CafeSdk == nullptr)
    {
        CafeSdk = new FIOSCafeSdk();
    }
    return CafeSdk;
}

static CafeCallbackObject *cafeCallbackObject = nil;

static void ListenNCSDKOpenURL(UIApplication* application, NSURL* url, NSString* sourceApplication, id annotation)
{
    [[NCSDKLoginManager getSharedInstance] finishNaverLoginWithURL:url];
}

FIOSCafeSdk::FIOSCafeSdk()
{
}

void FIOSCafeSdk::SetParentViewController() const
{
    [[NCSDKManager getSharedInstance] setParentViewController:[IOSAppDelegate GetDelegate].IOSController];
    [[NCSDKManager getSharedInstance] setNcSDKDelegate:cafeCallbackObject];
}


void FIOSCafeSdk::Init(FString ClientId, FString ClientSecret, int32 CafeId) const
{
    cafeCallbackObject = [[CafeCallbackObject alloc] init];
    [[NCSDKManager getSharedInstance] setNaverLoginClientId:ClientId.GetNSString()
                                     naverLoginClientSecret:ClientSecret.GetNSString()
                                                     cafeId:CafeId];
    [[NCSDKManager getSharedInstance] setOrientationIsLandscape:NO];
    FIOSCoreDelegates::OnOpenURL.AddStatic(&ListenNCSDKOpenURL);
}

void FIOSCafeSdk::StartHome() const
{
    dispatch_block_t block = ^{
        SetParentViewController();
        [[NCSDKManager getSharedInstance] presentMainViewController];
    };

    if (![[NSThread currentThread] isMainThread]) {
        dispatch_sync(dispatch_get_main_queue(), block);
    } else {
        block();
    }
}

void FIOSCafeSdk::StartNotice() const
{
    SetParentViewController();
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:1];
    });
}

void FIOSCafeSdk::StartEvent() const
{
    SetParentViewController();
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:2];
    });
}

void FIOSCafeSdk::StartMenu() const
{
    SetParentViewController();
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:3];
    });
}

void FIOSCafeSdk::StartMenuById(int32 MenuId) const
{
    SetParentViewController();
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[NCSDKManager getSharedInstance] presentArticleListViewControllerWithMenuId:MenuId];
    });
}

void FIOSCafeSdk::StartProfile() const
{
    SetParentViewController();
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:4];
    });
}

void FIOSCafeSdk::StartWrite(int32 MenuId, FString Subject, FString Text) const
{
    dispatch_block_t block = ^{
        SetParentViewController();
        [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithMenuId:MenuId
                                                                             subject:[NSString stringWithFString:Subject]
                                                                             content:[NSString stringWithFString:Text]];
    };
    
    if (![[NSThread currentThread] isMainThread]) {
        dispatch_sync(dispatch_get_main_queue(), block);
    } else {
        block();
    }
}

void FIOSCafeSdk::StartImageWrite(int32 MenuId, FString Subject, FString Text, FString ImageUri) const
{
    SetParentViewController();
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeImage
                                                                            menuId:MenuId
                                                                           subject:[NSString stringWithFString:Subject]
                                                                           content:[NSString stringWithFString:Text]
                                                                          filePath:[NSString stringWithFString:ImageUri]];
    });
}

void FIOSCafeSdk::StartVideoWrite(int32 MenuId, FString Subject, FString Text, FString VideoUri) const
{
    SetParentViewController();
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeVideo
                                                                            menuId:MenuId
                                                                           subject:[NSString stringWithFString:Subject]
                                                                           content:[NSString stringWithFString:Text]
                                                                          filePath:[NSString stringWithFString:VideoUri]];
    });    
}

bool FIOSCafeSdk::IsShow() const
{
    return false;
}

void FIOSCafeSdk::SyncGameUserId(FString GameUserId) const
{
    [[NCSDKManager getSharedInstance] syncGameUserId:[NSString stringWithFString:GameUserId]];
}

void FIOSCafeSdk::StartMore() const
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        SetParentViewController();        
        [[NCSDKManager getSharedInstance] presentEtc];
    });
}

@implementation CafeCallbackObject
#pragma mark - NCSDKDelegate
- (void)ncSDKViewDidLoad {
    FCafeSDKPluginModule::OnCafeSdkStarted.Broadcast();
}
- (void)ncSDKViewDidUnLoad {
    if ([NCSDKManager getSharedInstance].useWidget) {
        [[NCWidget getSharedInstance] setRootView:[IOSAppDelegate GetDelegate].RootView];
        [[NCWidget getSharedInstance] setNcWidgetDelegate:self];
        [[IOSAppDelegate GetDelegate].RootView addSubview:[NCWidget getSharedInstance].view];
        [[NCWidget getSharedInstance].view setHidden:NO];
    }
    
    FCafeSDKPluginModule::OnCafeSdkStopped.Broadcast();
}
- (void)ncSDKJoinedCafeMember {
    FCafeSDKPluginModule::OnCafeSdkJoined.Broadcast();
}
- (void)ncSDKPostedArticleAtMenu:(NSInteger)menuId {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.6 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        FCafeSDKPluginModule::OnCafeSdkPostedArticle.Broadcast(menuId);
    });
}
- (void)ncSDKPostedCommentAtArticle:(NSInteger)articleId {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.6 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        FCafeSDKPluginModule::OnCafeSdkPostedComment.Broadcast(articleId);
    });
}
- (void)ncSDKRequestScreenShot {
    FScreenshotRequest::RequestScreenshot("CafeSdkScreenshot.png", false, false);
}
- (void)ncWidgetPostArticle {
    GetSharedCafeSdk()->StartWrite(0, "", "");
}
- (void)ncWidtetExecuteGLink {
    GetSharedCafeSdk()->StartHome();
}
- (void)ncWidgetPostArticleWithImage {
    FScreenshotRequest::RequestScreenshot("CafeSdkScreenshot.png", false, false);
}
@end