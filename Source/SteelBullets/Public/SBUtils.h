#pragma once

class SBUtils
{
public:
	template <typename T>
	static T* GetSBPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		return Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass()));
	}
};
