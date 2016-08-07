// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TRIALTECH_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	
	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(Transient)
	class UBehaviourComponent* BehaviourComponent;
	
};
