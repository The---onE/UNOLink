#pragma once

#include "cocos2d.h"
USING_NS_CC;

/*
Ŀǰֻʵ����Android�˵��𶯹��ܣ���Ҫͨ��JNI����Java������Ҫ��Android�ļ��н����޸�
	����ϷĿ¼�� proj.android\src\org\cocos2dx\lib\Cocos2dxHelper.java �ļ����޸�
	�� public class Cocos2dxHelper ������ӣ��������Ӧ��
		public static void vibrate(int vibrateTime) {
			Vibrator vib = (Vibrator) sActivity.getSystemService(Service.VIBRATOR_SERVICE);
			vib.vibrate(vibrateTime);
		}
		public static void cancelVibrate() {
			Vibrator vib = (Vibrator) sActivity.getSystemService(Service.VIBRATOR_SERVICE);
			vib.cancel();
		}

	����ϷĿ¼�� proj.android\AndroidManifest.xml �����
		<uses-permission android:name="android.permission.VIBRATE"/>
*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif 

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

namespace Custom
{
	class Vibrator
	{
	public:
		static void vibrate(int time); //��ʼ�𶯣����룩
		static void cancelVibrate(); //ֹͣ��
	};
}
