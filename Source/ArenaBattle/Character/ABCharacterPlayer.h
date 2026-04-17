// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"
#include "ABCharacterPlayer.generated.h"

class UInputAction;

/**
 * 플레이어가 직접 조종하는 캐릭터 클래스입니다.
 * 향상된 입력(Enhanced Input) 시스템을 통해 캐릭터의 이동, 시야 회전, 점프 로직을 처리합니다.
 */
UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()

public:
	AABCharacterPlayer();

protected:
	virtual void BeginPlay() override;

	/** 플레이어의 입력 컴포넌트를 설정하고 액션과 함수를 바인딩합니다. */
	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent) override;

protected:
	// 이동 함수.
	/**
	 * 캐릭터 이동 입력을 처리합니다.
	 * @param Value 이동 액션에서 전달된 2D 벡터 (x: 좌우, y: 전후)
	 */
	void Move(const FInputActionValue& Value);

	/**
	 * 마우스를 이용한 시야 회전 입력을 처리합니다.
	 * @param Value 회전 액션에서 전달된 2D 벡터 (x: Yaw, Y: Pitch)
	 */
	void Look(const FInputActionValue& Value);

protected:
	// --- 컴포넌트 섹션 ---
	
	/** 캐릭터 뒤에서 카메라를 지탱하는 스태틱 암 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> SpringArm;

	/** 플레이어 시점을 제공하는 카메라 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> Camera;

	// --- 입력 에셋 섹션 ---.
protected:
	/** 기본 입력 매핑 컨텍스트 (IMC_Default) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	/** 이동 액션 (IA_Move) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> MoveAction;

	/** 시야 회전 액션 (IA_Look) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> LookAction;

	/** 점프 액션 (IA_Jump) */
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<UInputAction> JumpAction;
};
