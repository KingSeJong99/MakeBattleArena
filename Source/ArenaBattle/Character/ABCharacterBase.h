// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ABAnimationAttackInterface.h"
#include "Interface/ABCharacterWidgetInterface.h"
#include "Interface/ABCharacterItemInterface.h"
#include "ABCharacterBase.generated.h"

/** 캐릭터의 컨트롤 입력 방식을 정의하는 열거형 입니다. */
UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quarter
};

// 아이템 획득 처리를 위한 델리게이트 선언.
DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UABItemData* /*InItemData*/)

/**
 * 프로젝트 내 모든 캐릭터의 기본이 되는 베이스 클래스입니다.
 * 캐릭터의 기본적인 컨트롤 데이터 관리 및 콤보 공격 시스템의 핵심 로직을 포함합니다.
 * 이 클래스를 상속받아 실제 플레이어 캐릭터나 AI캐릭터를 구현합니다.
 */
UCLASS()
class ARENABATTLE_API AABCharacterBase 
	: public ACharacter, 
	public IABAnimationAttackInterface,
	public IABCharacterWidgetInterface,
	public IABCharacterItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

	/** 공격 감지 함수. */
	virtual void AttackHitCheck() override;

	/** 데미지 처리 함수. */
	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, 
		AActor* DamageCauser) override;

	/** Inherited via IABCharacterWidgetInterface */
	virtual void SetupCharacterWidget(
		UABUserWidget* InUserWidget) override;

	/** 모든 컴포넌트의 초기화가 끝나면 실행. */
	virtual void PostInitializeComponents() override;
	 
protected:
	// --- Dead ---

	/** 죽음 설정 함수. */
	virtual void SetDead();

	/** 죽는 애니메이션 재생 함수. */
	void PlayDeadAnimation();

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

	/** 컨트롤 타입 별 데이터 관리를 위한 맵. */
	virtual void TakeItem(UABItemData* InItemData) override;

	// 아이템 종류마다 처리될 함수.
	virtual void DrinkPotion(UABItemData* InItemData);
	virtual void EquipWeapon(UABItemData* InItemData);
	virtual void ReadScroll(UABItemData* InItemData);

	// 아이템 처리를 위한 델리게이트 관리 배열.
	TArray<FOnTakeItemDelegate> TakeItemActions;

protected:
	// 컨트롤 타입 별 데이터 관리를 위한 맵.
	UPROPERTY(EditAnywhere, Category = CharacterControl)
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

protected:
	/** 콤보 공격 몽타주. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	TObjectPtr<class UAnimMontage> ComboAttackMontage;

	/** 
	 * 현재 콤보 단계.\n 
	 * 0은 실행이 안된 상태이며, 1, 2, 3, 4로 단계가 구분 됩니다.
	 */	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	TObjectPtr<class UABComboActionData> ComboActionData;

	// 현재 콤보 단계 (0은 실행 안된 상태. 1/2/3/4로 단계 구분).
	UPROPERTY(EditAnywhere, Category = Attack)
	uint32 CurrentCombo = 0;

	/** 콤보 판정에 사용할 타이머. */
	FTimerHandle ComboTimerHandle;

	/** 콤보 점프를 판정할 때 사용할 플래그. */
	UPROPERTY(VisibleAnywhere, Category = Attack)
	bool bHasNextComboCommand = false;

protected:
	// --- Dead ---

	/** 죽음 몽타주. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dead)
	TObjectPtr<class UAnimMontage> DeadMontage;

	/** 죽은 후 대기할 시간 값(단위: 초). */
	float DeadEventDelayTime = 5.0f;

protected:
	/** 스탯 컴포넌트. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	TObjectPtr<class UABCharacterStatComponent> Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget)
	TObjectPtr<class UABWidgetComponent> HpBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment)
	TObjectPtr<class USkeletalMeshComponent> Weapon;
};
