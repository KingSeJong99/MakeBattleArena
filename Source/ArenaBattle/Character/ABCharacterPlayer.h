// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"
#include "ABCharacterPlayer.generated.h"

// 전방선언.
class UInputAction;

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()
	
public:
	AABCharacterPlayer();

protected:
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent) override;

	// 설정된 컨트롤에 따라 입력 매핑 컨텍스트 및 관련 설정 처리 함수.
	void SetCharacterControl(
		ECharacterControlType NewCharacterControlType
	);

	// 컨트롤 데이터 설정.
	virtual void SetCharacterContolData(
		const class UABCharacterControlData* InCharacterControlData) override;

protected:
	// 캐릭터 컨트롤 변경 입력 처리 함수.
	void ChangeCharacterControl();

	// 이동 함수.
	void ShoulderMove(const FInputActionValue& Value);

	// 회전 함수.
	void ShoulderLook(const FInputActionValue& Value);

	// 쿼터뷰일 때 이동 처리 함수.
	void QuarterMove(const FInputActionValue& Value);

	// 공격 함수.
	void Attack();

protected:
	// --- 컴포넌트 구성 ---
	
	/** 캐릭터 뒤에서 카메라를 지탱하는 스태틱 암 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> SpringArm;

	/** 플레이어 시점을 제공하는 카메라 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> Camera;

protected:

	// --- 입력 에셋 섹션 ---

	//UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	//TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	/** 이동 액션 (IA_Move) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> ShoulderMoveAction;

	/** 시야 회전 액션 (IA_Look) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> ShoulderLookAction;

	/** 점프 액션 (IA_Jump) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> JumpAction;

	/** 이동 액션 (IA_Move) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> QuarterMoveAction;

	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> ChangeControlAction;

	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> AttackAction;

	/** 현재 사용 중인 캐릭터 컨트롤 타입 */
	UPROPERTY(VisibleAnywhere, Category = CharacterControl)
	ECharacterControlType CurrentCharacterControlType;
};
