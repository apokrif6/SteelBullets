#pragma once

class SBUtils
{
public:
	template <typename T>
	static T* GetSBPlayerComponent(APawn* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		return Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass()));
	}
};
