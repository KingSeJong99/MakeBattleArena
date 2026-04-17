// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "Character/ABCharacterPlayer.h"

AABGameMode::AABGameMode()
{
	// 기본으로 스폰할 캐릭터 클래스를 지정합니다.
	// C++ 클래스를 직접 참조하여 런타임 안정성을 확보합니다.
	DefaultPawnClass = AABCharacterPlayer::StaticClass();

	// 블루프린트로 제작된 플레이어 컨트로럴러 에셋을 로드합니다.
	// _C 접미사는 블루프린트 클래스 자체를 참조하기 위해 필요합니다.
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerRef(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonPlayerController.BP_ThirdPersonPlayerController_C")
	);

	if (PlayerControllerRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerRef.Class;
	}
}
