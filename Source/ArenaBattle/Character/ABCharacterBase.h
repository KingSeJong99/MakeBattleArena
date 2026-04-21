// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

/** 캐릭터의 컨트롤 입력 방식을 정의하는 열거형 입니다. */
UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quarter
};

/**
 * 프로젝트 내 모든 캐릭터의 기본이 되는 베이스 클래스입니다.
 * 캐릭터의 기본적인 컨트롤 데이터 관리 및 콤보 공격 시스템의 핵심 로직을 포함합니다.
 * 이 클래스를 상속받아 실제 플레이어 캐릭터나 AI캐릭터를 구현합니다.
 */
UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

protected:

	/** 컨트롤 데이터 설정. */
	virtual void SetCharacterContolData(
		const class UABCharacterControlData* InCharacterControlData
	);
	
	/** 
	 * 콤보 공격 처리 함수.\n
	 * 공격을 처음 시작할 때와 콤보 액션을 진행합니다.
	 */
	void ProcessComboCommand();
	
	/** 콤보 공격이 시작될 때 실행할 함수. */
	void ComboActionBegin();
	
	/** 몽타주 재생 종료 시 호출할 함수 (델리게이트와 연동). */
	void ComboActionEnd(UAnimMontage* TargetMontage, bool bInterrupted);
	
	/** 콤보 타이머 설정 함수. */
	void SetComboCheckTimer();
	
	/** 
	 * 콤보 타이밍 처리 함수. \n
	 * 타이머를 설정하고, 설정한 시간을 지나면 실행합니다.
	 * 시간 전에 공격 입력이 제대로 들어왔는지 확인을 해야 합니다.
	 */
	void ComboCheck();
	
protected:
	/** 컨트롤 타입 별 데이터 관리를 위한 맵. */
	UPROPERTY(EditAnywhere, Category = CharacterControl)
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;
	
protected:
	/** 콤보 공격 몽타주. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	TObjectPtr<class UAnimMontage> ComboAttackMontage;
	
	/** 콤보 액션 처리 데이터. */
	UPROPERTY(EditAnywhere, Category = Attack)
	TObjectPtr<class UABComboActionData> ComboActionData;
	
	/** 현재 콤보 단계.\n 
	 * 0은 실행이 안된 상태이며, 1, 2, 3, 4로 단계가 구분 됩니다.
	 */
	UPROPERTY(EditAnywhere, Category = Attack)
	uint32 CurrentCombo = 0;
	
	/** 콤보 판정에 사용할 타이머. */
	FTimerHandle ComboTimerHandle;
	
	/** 콤보 점프를 판정할 때 사용할 플래그. */
	UPROPERTY(VisibleAnywhere, Category = Attack)
	bool bHasNextComboCommand = false;
};
