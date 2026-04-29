// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackHitCheck.h"
#include "Interface/ABAnimationAttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(
	USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	/** 
	 * AnimNotify가 배치된 애니메이션을 사용(소유)하는 폰에 접근하여 공격 판정하도록 함수 실행.
	   인터페이스를 활용하여 다른 객체에 접근해야할 때 알고 싶은 정보만 노출할 수 있습니다.
	 * 인터페이스의 장점: 결합도를 낮추는 설계를 할 수 있습니다.
	 * 인터페이스의 단점: 계층적 구조로 인해 복잡도가 늘어날 수 있으며 디버깅이 복잡해질 수
	   있습니다.
	 */
	if (MeshComp)
	{
		/** MeshComponent를 소유하는 액터를 원하는 인터페이스 타입으로 변환. */
		IABAnimationAttackInterface* AttackPawn 
			= Cast<IABAnimationAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
