#include "CatmullRomGeometryActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

ACatmullRomGeometryActor::ACatmullRomGeometryActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACatmullRomGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    GenerateGeometry();
}

void ACatmullRomGeometryActor::GenerateGeometry()
{
    USplineComponent* SplineComponent = NewObject<USplineComponent>(this);
    SplineComponent->RegisterComponent();
    SplineComponent->SetWorldLocation(GetActorLocation());
    SplineComponent->ClearSplinePoints();

    for (const FVector& ControlPoint : ControlPoints)
    {
        SplineComponent->AddSplinePoint(ControlPoint, ESplineCoordinateSpace::World, false);
    }

    SplineComponent->UpdateSpline();

    int32 NumSegments = SplineComponent->GetNumberOfSplinePoints() - 1;

    for (int32 i = 0; i < NumSegments; ++i)
    {
        USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this);
        SplineMeshComponent->SetMobility(EComponentMobility::Movable);
        SplineMeshComponent->RegisterComponent();
        SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::X);
        SplineMeshComponent->SetStaticMesh(GeometryMesh);
        SplineMeshComponent->SetMaterial(0, GeometryMaterial);

        FVector StartPos, StartTangent, EndPos, EndTangent;
        SplineComponent->GetLocationAndTangentAtSplinePoint(i, StartPos, StartTangent, ESplineCoordinateSpace::World);
        SplineComponent->GetLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent, ESplineCoordinateSpace::World);

        SplineMeshComponent->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);
        SplineMeshComponent->SetStartScale(FVector2D(Width, 1.f));
        SplineMeshComponent->SetEndScale(FVector2D(Width, 1.f));
    }
}
