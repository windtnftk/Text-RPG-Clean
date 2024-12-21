#pragma once
class IEvent {
public:
    virtual ~IEvent() = default;
    virtual void trigger(int depth) const = 0;
    virtual std::unique_ptr<IEvent> clone() const = 0;
};
