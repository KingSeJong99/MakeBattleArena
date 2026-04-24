// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "Player/ABPlayerController.h"
#include "Character/ABCharacterPlayer.h"

AABGameMode::AABGameMode()
{
	/** 기본으로 스폰할 캐릭터 클래스를 지정합니다.
	 *  C++ 클래스를 직접 참조하여 런타임 안정성을 확보합니다.
	 */
	DefaultPawnClass = AABCharacterPlayer::StaticClass();

	/** 기본 플레이어 컨트롤러 클래스 설정. */
	PlayerControllerClass = AABPlayerController::StaticClass();
}
