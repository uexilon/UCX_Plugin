// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedCollisionBPLibrary.h"
#include "AdvancedCollision.h"
#include "PhysXPublic.h"

UAdvancedCollisionBPLibrary::UAdvancedCollisionBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

int32 UAdvancedCollisionBPLibrary::AdvancedCollisionSampleFunction(const UStaticMeshComponent* staticMeshComponent, const FVector& start, const FVector& end)
{
	TArray<FKConvexElem> convexElements = staticMeshComponent->GetStaticMesh()->BodySetup->AggGeom.ConvexElems;
	for (int32 i = 0; i < convexElements.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Element Index is: %d"), i);
		FString s = convexElements[i].GetName().ToString();
		TArray<int32> indicies = TArray<int32>(convexElements[i].IndexData);
		FOccluderVertexArray verArray = convexElements[i].VertexData;
		TArray<FVector> verticies = TArray<FVector>(verArray);
		FVector intersectPoint;
		FVector normal;
		if (FMath::SegmentTriangleIntersection(start, end, staticMeshComponent->GetComponentTransform().TransformPosition(verticies[0]), staticMeshComponent->GetComponentTransform().TransformPosition(verticies[3]), staticMeshComponent->GetComponentTransform().TransformPosition(verticies[1]), intersectPoint, normal))
		{
			return i;
		}
		if (FMath::SegmentTriangleIntersection(start, end, staticMeshComponent->GetComponentTransform().TransformPosition(verticies[3]), staticMeshComponent->GetComponentTransform().TransformPosition(verticies[2]), staticMeshComponent->GetComponentTransform().TransformPosition(verticies[1]), intersectPoint, normal))
		{
			return i;
		}
		/*for (int32 j = 0; j < indicies.Num() / 3; j++)
		{
			FVector intersectPoint;
			FVector normal;
			if (FMath::SegmentTriangleIntersection(start, end, verticies[j], verticies[j + 1], verticies[j + 2], intersectPoint, normal)) 
			{
				return i;
			}
		}*/
		

		UE_LOG(LogTemp, Warning, TEXT("Element Index is: %s"), *s);

		
	}
	return -1;
}



