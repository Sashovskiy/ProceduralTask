// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

#include "MyTestActor.generated.h"

UCLASS()
class PROCEDURALTASK_API AMyTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallParameters)
	float WallHeight = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallParameters)
	float WallLength = 900;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallParameters)
	float WallWidth = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindowParameters)
		float WindowHeight = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindowParameters)
		float WindowLength = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindowParameters)
		FVector2D WindowOffset = FVector2D(300,200);

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostActorCreated();
	virtual void PostLoad();
	void CreateTriangle();
private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* mesh;

	int32 SectionIndex = 0;
	void WallAdd(float f_Length, float f_Height, float s_Length, float s_Height, bool isForwardSide);
	
	void FirstEndOfWall(float f_Length, float f_Height);
	void SecondEndOfWall(float f_Length, float f_Height, float s_Length, float s_Height);
	void setMaterialtoWall();

	
	
	
};
