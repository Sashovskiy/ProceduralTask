// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestActor.h"
#include "Runtime/Engine/Classes/Materials/Material.h"

// Sets default values
AMyTestActor::AMyTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	// New in UE 4.17, multi-threaded PhysX cooking.
	mesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	CreateTriangle();
}

// Called every frame
void AMyTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTestActor::PostActorCreated()
{
	Super::PostActorCreated();
	CreateTriangle();
}

// This is called when actor is already in level and map is opened
void AMyTestActor::PostLoad()
{
	Super::PostLoad();
	CreateTriangle();
}

void AMyTestActor::CreateTriangle()
{
	//FillWall(0);
//	FillWall(WallLength + WindowLength);
	
	WallAdd(WindowOffset.X, WallHeight, 0.f, 0.f, true);

	WallAdd(WallLength- (WindowOffset.X + WindowLength), WallHeight, (WindowOffset.X + WindowLength), 0.f, true);

	WallAdd(WindowLength, WindowOffset.Y, WindowOffset.X, 0.f, true);

	WallAdd(WindowLength, WallHeight -(WindowHeight + WindowOffset.Y), WindowOffset.X, WindowHeight+ WindowOffset.Y, true);

	FirstEndOfWall(WallLength, WallHeight);
	SecondEndOfWall(WindowLength, WindowHeight, WindowOffset.X, WindowOffset.Y);
	setMaterialtoWall();

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
}



void AMyTestActor::WallAdd(float f_Length, float f_Height, float s_Length, float s_Height, bool isForwardSide)
{
	float f_Width = (isForwardSide) ? 0 : WallWidth;

	TArray<FVector> vertices;
	vertices.Add(FVector(f_Width, s_Length, s_Height));
	vertices.Add(FVector(f_Width, s_Length + f_Length, s_Height));
	vertices.Add(FVector(f_Width, s_Length, s_Height + f_Height));
	vertices.Add(FVector(f_Width, s_Length + f_Length,  s_Height));
	vertices.Add(FVector(f_Width, s_Length + f_Length, s_Height + f_Height));
	vertices.Add(FVector(f_Width, s_Length, s_Height + f_Height));

	TArray<int32> Triangles;
	for (auto i : vertices)
	{
		Triangles.Add((isForwardSide) ? Triangles.Num() : (vertices.Num() - Triangles.Num() - 1));
	}
	
	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(0, 10));

	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

	mesh->CreateMeshSection_LinearColor(SectionIndex++, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
	if (isForwardSide)
		WallAdd(f_Length, f_Height, s_Length, s_Height, !isForwardSide);

}

void AMyTestActor::FirstEndOfWall(float f_Length, float f_Height)
{
	TArray<FVector> vertices;
	//Left Section
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(0, 0, f_Height));
	vertices.Add(FVector(WallWidth, 0, 0));
	vertices.Add(FVector(WallWidth, 0, f_Height));
	vertices.Add(FVector(WallWidth, 0, 0));
	vertices.Add(FVector(0, 0, f_Height));
	
	

	//Down Section
vertices.Add(FVector(WallWidth, f_Length, 0));
vertices.Add(FVector(0, f_Length, 0));
vertices.Add(FVector(WallWidth, 0, 0));
vertices.Add(FVector(0, 0, 0));
vertices.Add(FVector(WallWidth, 0, 0)); 
vertices.Add(FVector(0, f_Length, 0));

//Right Section

vertices.Add(FVector(0, f_Length, f_Height));
vertices.Add(FVector(0, f_Length, 0));
vertices.Add(FVector(WallWidth, f_Length, f_Height));
vertices.Add(FVector(WallWidth, f_Length, 0));
vertices.Add(FVector(WallWidth, f_Length, f_Height));
vertices.Add(FVector(0, f_Length, 0));

//Up Section
vertices.Add(FVector(0, 0, f_Height));
vertices.Add(FVector(0, f_Length, f_Height));
vertices.Add(FVector(WallWidth, 0, f_Height));
vertices.Add(FVector(WallWidth, f_Length, f_Height));
vertices.Add(FVector(WallWidth, 0, f_Height));
vertices.Add(FVector(0, f_Length, f_Height));

	

	TArray<int32> Triangles;
	for (auto i : vertices)
	{
		Triangles.Add(Triangles.Num());
	}

	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	for (int i = 0; i < (vertices.Num()/3); i++)
	{
		UV0.Add(FVector2D(0, 0));
		UV0.Add(FVector2D(10, 0));
		UV0.Add(FVector2D(0, 10));
	}
	/*UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(0, 10));
*/
	TArray<FProcMeshTangent> tangents;
	for (auto i : vertices)
	{
		tangents.Add(FProcMeshTangent(0, 1, 0));
	}
	/*tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));*/

	TArray<FLinearColor> vertexColors;
	for (auto i : vertices)
	{
		vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	}
	/*vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));*/

	mesh->CreateMeshSection_LinearColor(SectionIndex++, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
}

void AMyTestActor::SecondEndOfWall(float f_Length, float f_Height, float s_Length, float s_Height)
{	TArray<FVector> vertices;
	//Left Section
	vertices.Add(FVector(0, s_Length, s_Height));
	vertices.Add(FVector(0, s_Length, f_Height+ s_Height));
	vertices.Add(FVector(WallWidth, s_Length, s_Height));
	vertices.Add(FVector(WallWidth, s_Length, s_Height +f_Height));
	vertices.Add(FVector(WallWidth, s_Length, s_Height));
	vertices.Add(FVector(0, s_Length, f_Height+ s_Height));
	


	//Down Section
vertices.Add(FVector(WallWidth, f_Length+ s_Length, s_Height));
vertices.Add(FVector(0, f_Length+ s_Length, s_Height));
vertices.Add(FVector(WallWidth, s_Length, s_Height));
vertices.Add(FVector(0, s_Length, s_Height));
vertices.Add(FVector(WallWidth, s_Length, s_Height));
vertices.Add(FVector(0, f_Length+ s_Length, s_Height));

//Right Section

vertices.Add(FVector(0, f_Length+ s_Length, f_Height+ s_Height));
vertices.Add(FVector(0, f_Length+ s_Length, s_Height));
vertices.Add(FVector(WallWidth, f_Length + s_Length, f_Height+ s_Height));
vertices.Add(FVector(WallWidth, f_Length + s_Length, s_Height));
vertices.Add(FVector(WallWidth, f_Length + s_Length, f_Height+ s_Height));
vertices.Add(FVector(0, f_Length + s_Length, s_Height));





//Up Section
vertices.Add(FVector(0, s_Length, f_Height+ s_Height));
vertices.Add(FVector(0, f_Length + s_Length, f_Height+ s_Height));
vertices.Add(FVector(WallWidth, s_Length, f_Height+ s_Height));
vertices.Add(FVector(WallWidth, f_Length + s_Length, f_Height+ s_Height));
vertices.Add(FVector(WallWidth, s_Length, f_Height+ s_Height));
vertices.Add(FVector(0, f_Length + s_Length, f_Height+ s_Height));

	

	TArray<int32> Triangles;
	for (auto i : vertices)
	{
		Triangles.Add( (vertices.Num() - Triangles.Num() - 1));
	}

	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	for (int i = 0; i < (vertices.Num()/3); i++)
	{
		UV0.Add(FVector2D(0, 0));
		UV0.Add(FVector2D(10, 0));
		UV0.Add(FVector2D(0, 10));
	}
	/*UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(0, 10));
*/
	TArray<FProcMeshTangent> tangents;
	for (auto i : vertices)
	{
		tangents.Add(FProcMeshTangent(0, 1, 0));
	}
	/*tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));*/

	TArray<FLinearColor> vertexColors;
	for (auto i : vertices)
	{
		vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	}
	/*vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));*/

	mesh->CreateMeshSection_LinearColor(SectionIndex++, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
}

void AMyTestActor::setMaterialtoWall()
{
	UMaterial* TheMaterial = LoadObject<UMaterial>(nullptr, TEXT("Material'/AnimationSharing/AnimSharingBase.AnimSharingBase'"));
	//SetMaterial(0, TheMaterial);
	for (int32 i = 0; i <= SectionIndex; i++)
	{
		mesh->SetMaterial(i, TheMaterial);
			
	}
}

