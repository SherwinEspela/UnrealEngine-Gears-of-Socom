// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTaskEnableValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskEnableValue::UBTTaskEnableValue()
{
	NodeName = TEXT("Enable Value");
}

EBTNodeResult::Type UBTTaskEnableValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	return EBTNodeResult::Succeeded;
}
