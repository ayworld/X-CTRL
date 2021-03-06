#include "FileGroup.h"
#include "DisplayPrivate.h"

/*字库*/
#include "FreeSerif9pt7b.h"

#define START_Y (StatusBar_Height + (screen.height() - StatusBar_Height - TEXT_HEIGHT_1 * 2 - 12) * 0.5f)

static LightGUI::ProgressBar<SCREEN_CLASS> GameProgress(&screen, 0, screen.height() - 10, screen.width(), 10, 0);
static float progress;

/**
  * @brief  页面初始化事件
  * @param  无
  * @retval 无
  */
static void Setup()
{
    GameProgress.Color_FM = screen.Black;
    progress = 0.0f;

    ClearPage();

    screen.setTextColor(screen.White);
    screen.setTextSize(1);
    screen.setFont(&FreeSerif9pt7b);
    screen.setCursor((screen.width() - 90) / 2, START_Y);
    screen.print("VIFEXTech");

    screen.setFont();
    screen.setTextSize(1);
    screen.setCursor(TextMid(0.5f, 7 + strlen(_X_CTRL_VERSION)), START_Y + TEXT_HEIGHT_1);
    screen << "X-CTRL " << _X_CTRL_VERSION;
    screen.setCursor(TextMid(0.5f, strlen(__DATE__) + 6), START_Y + TEXT_HEIGHT_1 * 2 + 2);
    screen << __DATE__ << " Build";
    XFS_Speak("X-Control固件版本:%s,编译时间:%s,%s", _X_CTRL_VERSION, __DATE__, __TIME__);
    XFS_Speak("设计者:VIFAX Technology");
}

/**
  * @brief  页面循环事件
  * @param  无
  * @retval 无
  */
static void Loop()
{
    GameProgress.Color_PB = progress * 0xFFFF;
    GameProgress.setProgress(progress);

    if(progress >= 1.0f)
    {
        if(btUP)
        {
            page.PagePush(PAGE_GameDoom);
        }
        else
        {
            page.PagePush(PAGE_GameHopper);
        }
        PageDelay(200);
    }

    if(!btOK && progress > 0.0f)
    {
        __IntervalExecute(progress -= 0.005f, 5);
    }
}

/**
  * @brief  页面退出事件
  * @param  无
  * @retval 无
  */
static void Exit()
{
    ClearPage();
}

/**
  * @brief  页面事件
  * @param  无
  * @retval 无
  */
static void Event(int event, void* param)
{
    if(event == EVENT_ButtonPress)
    {
        if(btBACK)
            page.PagePop();
    }
    if(event == EVENT_ButtonLongPressRepeat)
    {
        if(btOK)
        {
            progress += 0.05f;
        }
    }
}

/**
  * @brief  设计者信息页面注册
  * @param  pageID:为此页面分配的ID号
  * @retval 无
  */
void PageRegister_About(uint8_t pageID)
{
    page.PageRegister(pageID, Setup, Loop, Exit, Event);
}
