// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTargetDummy.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionComponent.h"
#include "Components/StaticMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RogueTargetDummy)


ARogueTargetDummy::ARogueTargetDummy()
{
	SkelMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = SkelMeshComp;

	ActionComp = CreateDefaultSubobject<URogueActionComponent>(TEXT("ActionComp"));
	ActionComp->SetDefaultAttributeSet(FRogueHealthAttributeSet::StaticStruct());
}


void ARogueTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FRogueAttribute* FoundAttribute = ActionComp->GetAttribute(SharedGameplayTags::Attribute_Health);
	FoundAttribute->OnAttributeChanged.AddUObject(this, &ThisClass::OnHealthChanged);
}


void ARogueTargetDummy::OnHealthChanged(float NewValue, const FAttributeModification& AttributeMod)
{
	if (AttributeMod.Magnitude < 0.0f)
	{
		SkelMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}