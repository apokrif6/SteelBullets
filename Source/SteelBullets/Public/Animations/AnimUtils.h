#pragma once

class AnimUtils
{
public:
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* AnimSequenceBase)
	{
		if (!AnimSequenceBase) return nullptr;

		const auto NotifyEvents = AnimSequenceBase->Notifies;

		for (auto NotifyEvent : NotifyEvents)
		{
			const auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (!AnimNotify) continue;

			return AnimNotify;
		}

		return nullptr;
	}
};
