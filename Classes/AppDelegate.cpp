#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "TetrisBoardScene.h"
#include <sqlite3.h>

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static void initializeDatabase();
int callback(void *count, int argc, char **argv, char **azColName) 
{
	// increment count
	(*((int*)count))++;

	return 0;
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {

		// Setting Design Resolution to Medium Resolution
		designResolutionSize = mediumResolutionSize;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("TetrisCocos", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		//glview = GLViewImpl::createWithFullScreen("TetrisCocos");
#else
        glview = GLViewImpl::create("TetrisCocos");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

	// initialize database
	initializeDatabase();

    // create a scene. it's an autorelease object
	//auto scene = MainMenuScene::createScene();
	auto scene = TetrisBoardScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}


void initializeDatabase()
{
	sqlite3 * db;
	char *errorMsg;

	// open db, create if doesn't exist
	if (sqlite3_open("single_player_db", &db))
	{
		cocos2d::log("can't open single_player_db database");
		cocos2d::log(sqlite3_errmsg(db));
	}
	else
	{
		cocos2d::log("db opend/created succefully");

		// create table if doesn't exist
		char *query = "create table if not exists single_player_table(" \
			"name text primary key not null," \
			"score int," \
			"max_level int );";

		int rc = sqlite3_exec(db, query, NULL, 0, &errorMsg);
		if (rc != SQLITE_OK)
		{
			cocos2d::log("(create table if doesn't exist) sql error");
			cocos2d::log(errorMsg);
			sqlite3_free(errorMsg);
		}
		else
		{
			cocos2d::log("table present/created succefully");

			// create entry for player if not exist
			query = "select score from single_player_table where name = 'player'";
			int count = 0;
			rc = sqlite3_exec(db, query, callback, (void*)&count, &errorMsg);
			if (rc != SQLITE_OK)
			{
				cocos2d::log("(create entry for player if not exist) sql error");
				cocos2d::log(errorMsg);
				sqlite3_free(errorMsg);
			}
			else
			{
				if (count == 0)
				{
					// create row
					query = "insert into single_player_table (name, score, max_level) " \
						"values ('player', 0, 1 );";
					rc = sqlite3_exec(db, query, NULL, 0, &errorMsg);
					if (rc != SQLITE_OK)
					{
						cocos2d::log("(init single_player_table) sql error");
						cocos2d::log(errorMsg);
						sqlite3_free(errorMsg);
					}
					else
					{
						cocos2d::log("single_player_table successfully initialized");
					}
				}
				else if (count == 1)
				{
					//  well and good
					cocos2d::log("player recored present in table");
				}
			}
		}

	}
	sqlite3_close(db);
}