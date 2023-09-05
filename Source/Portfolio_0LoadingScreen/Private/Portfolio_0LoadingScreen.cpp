// Copyright Epic Games, Inc. All Rights Reserved.

#include "Portfolio_0LoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"
#include "Engine/Font.h"

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time
struct FPortfolio_0LoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FPortfolio_0LoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CachedResourceObject = GetResourceObject())
			Collector.AddReferencedObject(CachedResourceObject);
	}
};

class SPortfolio_0LoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPortfolio_0LoadingScreen) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs)
	{
		// Load, Path is hardcoded because this loads very early in startup
		static const FName TitleOverlay(TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/Overlay_Title_Game.Overlay_Title_Game"));
		TitleOverlayBrush = MakeShareable(new FPortfolio_0LoadingScreenBrush(TitleOverlay, FVector2D(900, 140)));

		static const FName Background(TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/BQ.BQ"));
		BackgroundBrush = MakeShareable(new FPortfolio_0LoadingScreenBrush(Background, FVector2D(1920, 1080)));

		const FText Title = FText::FromString(TEXT("Blades & Sorceries"));
		UFont* Font = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), nullptr, TEXT("/Game/Font/Berry_Rotunda_Font")));

		FSlateFontInfo FontInfo;
		FontInfo.FontObject = Font;
		FontInfo.Size = 36;

		ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(BackgroundBrush.Get())
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.Padding(FMargin(0.f, 0.f, 100.f, 5.f))
				[
					SNew(SImage)
					.Image(TitleOverlayBrush.Get())
				]
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(Title)
				.Font(FontInfo)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(24.0f))
				[
					SNew(SCircularThrobber)
					.Radius(24.f)
					.Visibility(this, &SPortfolio_0LoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	EVisibility GetLoadIndicatorVisibility() const
	{
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}
	
	/** Loading screen Images Brush */
	TSharedPtr<FSlateDynamicImageBrush> TitleOverlayBrush;
	TSharedPtr<FSlateDynamicImageBrush> BackgroundBrush;
};

class FPortfolio_0LoadingScreenModule : public IPortfolio_0LoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		// Force Load (for Cooker reference)
		LoadObject<UObject>(nullptr, TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/Overlay_Title_Game.Overlay_Title_Game") );
		LoadObject<UObject>(nullptr, TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/BQ.BQ"));

		// Why CreateScreen() on Startup? Resources are not loaded yet, views are breaking. And also it's overriding the other Intro Movies.
		/*if (IsMoviePlayerEnabled())
			CreateScreen();*/
	}
	
	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
		LoadingScreen.bWaitForManualStop = bPlayUntilStopped;
		LoadingScreen.bAllowEngineTick = bPlayUntilStopped;
		LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreen.WidgetLoadingScreen = SNew(SPortfolio_0LoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 0.f;
		LoadingScreen.WidgetLoadingScreen = SNew(SPortfolio_0LoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FPortfolio_0LoadingScreenModule, Portfolio_0LoadingScreen);