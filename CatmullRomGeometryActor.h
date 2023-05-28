

    
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatmullRomGeometryActor.generated.h"

    UCLASS()
        class CMUL_API ACatmullRomGeometryActor : public AActor
    {
        GENERATED_BODY()

    public:
        ACatmullRomGeometryActor();

        UPROPERTY(EditAnywhere, Category = "Geometry")
            TArray<FVector> ControlPoints;

        UPROPERTY(EditAnywhere, Category = "Geometry")
            UTexture2D* TextureFile;

        UPROPERTY(EditAnywhere, Category = "Geometry")
            float Width;

        UPROPERTY(EditAnywhere, Category = "Geometry")
            UStaticMesh* GeometryMesh;

        UPROPERTY(EditAnywhere, Category = "Geometry")
            UMaterialInterface* GeometryMaterial;
    protected:
        virtual void BeginPlay() override;

    private:
        void GenerateGeometry();
    };
