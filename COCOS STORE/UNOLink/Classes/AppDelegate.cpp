#include "AppDelegate.h"
#include "Scene/StartScene.h"
#include "Data/AudioData.h"

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("UNOLink", Rect(0, 0, 640, 960)); //´´½¨WINDOWS´°¿Ú
        director->setOpenGLView(glview);
	}

    director->getOpenGLView()->setDesignResolutionSize(WIDTH, HEIGHT, ResolutionPolicy::SHOW_ALL); //ÆÁÄ»ÊÊÅä
    director->setDisplayStats(false); //²»ÏÔÊ¾FPS
	director->setAnimationInterval(1.0 / 60); //ÉèÖÃFPS

	srand(time(NULL)); //ÉèÖÃËæ»úÊýÖÖ×Ó

	//Ô¤¼ÓÔØÒôÀÖÒôÐ§
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic(BGM);
	audio->preloadEffect(START_LINK_EFFECT);
	audio->preloadEffect(LINK_EFFECT);
	audio->preloadEffect(UNDO_EFFECT);
	audio->preloadEffect(REMOVE_EFFECT);
	audio->preloadEffect(WRONG_REMOVE_EFFECT);
	audio->preloadEffect(GAME_OVER_EFFECT);
	audio->preloadEffect(NEW_RECORD_EFFECT);

	//¼ÓÔØcocos studioµ¼³öµÄÎÄ¼þ
    FileUtils::getInstance()->addSearchPath("res");

	//½øÈëStart³¡¾°
    auto scene = StartScene::create();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	//Èô±³¾°ÒôÀÖ¿ªÆô£¬ÔÝÍ£±³¾°ÒôÀÖ
 	if (UserDefault::getInstance()->getBoolForKey(BGM_UD, BGM_DEFAULT_FLAG))
 		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

	//Èô±³¾°ÒôÀÖ¿ªÆô£¬»Ö¸´±³¾°ÒôÀÖ
 	if (UserDefault::getInstance()->getBoolForKey(BGM_UD, BGM_DEFAULT_FLAG))
 		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
