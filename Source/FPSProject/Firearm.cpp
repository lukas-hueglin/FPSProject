// Fill out your copyright notice in the Description page of Project Settings.


#include "Firearm.h"

// Sets default values
AFirearm::AFirearm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup root mesh
	RootMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Root"));
	RootMesh->bCastDynamicShadow = false;
	RootMesh->CastShadow = false;

	//Setup Attachments
	AttachmentComponent.AssistPlunger.SocketName = FName("AssistPlunger");
	AttachmentComponent.Barrel.SocketName = FName("Barrel");
	AttachmentComponent.Bolt.SocketName = FName("Bolt");
	AttachmentComponent.BoltCatch.SocketName = FName("BoltCatch");
	AttachmentComponent.BufferSystem.SocketName = FName("BufferSystem");
	AttachmentComponent.ChargingHandle.SocketName = FName("ChargingHandle");
	AttachmentComponent.EjectionCover.SocketName = FName("EjectionCover");
	AttachmentComponent.Gasblock.SocketName = FName("Gasblock");
	AttachmentComponent.LowerReceiver.SocketName = FName("LowerReceiver");
	AttachmentComponent.MagazineCatch.SocketName = FName("MagazineCatch");
	AttachmentComponent.ModeSwitch.SocketName = FName("ModeSwitch");
	AttachmentComponent.PistolGrip.SocketName = FName("PistolGrip");
	AttachmentComponent.Rail.SocketName = FName("Rail");
	AttachmentComponent.Stock.SocketName = FName("Stock");
	AttachmentComponent.Trigger.SocketName = FName("Trigger");
	AttachmentComponent.UpperReceiver.SocketName = FName("UpperReceiver");

	AttachmentComponent.AssistPlunger.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AssistPlunger"));
	AttachmentComponent.Barrel.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	AttachmentComponent.Bolt.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bolt"));
	AttachmentComponent.BoltCatch.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoltCatch"));
	AttachmentComponent.BufferSystem.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BufferSystem"));
	AttachmentComponent.ChargingHandle.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChargingHandle"));
	AttachmentComponent.EjectionCover.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EjectionCover"));
	AttachmentComponent.Gasblock.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gasblock"));
	AttachmentComponent.LowerReceiver.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LowerReceiver"));
	AttachmentComponent.MagazineCatch.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagazineCatch"));
	AttachmentComponent.ModeSwitch.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModeSwitch"));
	AttachmentComponent.PistolGrip.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolGrip"));
	AttachmentComponent.Rail.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rail"));
	AttachmentComponent.Stock.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stock"));
	AttachmentComponent.Trigger.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger"));
	AttachmentComponent.UpperReceiver.MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpperReceiver"));
}

// Called when the game starts or when spawned
void AFirearm::BeginPlay()
{
	Super::BeginPlay();
	
	// Set Active Layout
	ActiveLayout = Layouts[0];

	// Set all attachments to the attachments in ActiveLayout
	UpdateAttachment(AttachmentComponent.AssistPlunger);
	UpdateAttachment(AttachmentComponent.Barrel);
	UpdateAttachment(AttachmentComponent.Bolt);
	UpdateAttachment(AttachmentComponent.BoltCatch);
	UpdateAttachment(AttachmentComponent.BufferSystem);
	UpdateAttachment(AttachmentComponent.ChargingHandle);
	UpdateAttachment(AttachmentComponent.EjectionCover);
	UpdateAttachment(AttachmentComponent.Gasblock);
	UpdateAttachment(AttachmentComponent.LowerReceiver);
	UpdateAttachment(AttachmentComponent.MagazineCatch);
	UpdateAttachment(AttachmentComponent.ModeSwitch);
	UpdateAttachment(AttachmentComponent.PistolGrip);
	UpdateAttachment(AttachmentComponent.Rail);
	UpdateAttachment(AttachmentComponent.Stock);
	UpdateAttachment(AttachmentComponent.Trigger);
	UpdateAttachment(AttachmentComponent.UpperReceiver);
}

// Called every frame
void AFirearm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to update an attachment
void AFirearm::UpdateAttachment(FAttachment Attachment) 
{
	// Set Attachment to the new Attachment from the Layout
	if (ActiveLayout != NULL)
	{
		Attachment.Mesh = ActiveLayout->FindRow<FAttachment>(Attachment.SocketName, "", false)->Mesh;
		Attachment.Material = ActiveLayout->FindRow<FAttachment>(Attachment.SocketName, "", false)->Material;
	}

	// set the material
	Attachment.Mesh->SetMaterial(0, Attachment.Material);

	// attach the new mesh to the socket
	Attachment.MeshComponent->SetStaticMesh(Attachment.Mesh);
	Attachment.MeshComponent->AttachToComponent(RootMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), Attachment.SocketName);
}

