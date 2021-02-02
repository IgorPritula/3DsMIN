//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <functional>
#include "Event.hpp"

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                EventType GetEventType() const override { return EventType::type; }\
                                const char* GetName() const override { return #type; }

enum EventType {
    KeyPressed, KeyReleased,
    MouseMoved,
    FramebufferResize, WindowResize, WindowMove,
    ImGuiViewportResize
};

class Event {
public:
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
};

class EventDispatcher {
public:
        
    // Exapmle to use:
    //  EventDispatcher &eventDisp = EventDispatcher::getInstance();
    //  std::function<void(KeyPressedEvent&)> f = std::bind(&Camera::OnKeyPress, this, std::placeholders::_1);
    //  eventDisp.subscribe(EventType::KeyPressed, f);
    template<typename F>
    void subscribe(EventType type, std::function<void(F)> func) {
        std::function<void(Event&)> new_func = [=](Event& event){
            func(static_cast<F>(event));
        };
        m_Events[type].push_back(new_func);
    }
    
    // Example to use:
    //  EventDispatcher &eventDisp = EventDispatcher::getInstance();
    //  eventDisp.subscribe<KeyReleasedEvent>(&Camera::OnKeyPress, this);
    template<class E_class, typename F, class F_class>
    void subscribe(void (F_class::*func)(F), void* class_p) {
        
        F_class* c_p = (F_class*)class_p;
        std::function<void(E_class&)> bind_f = std::bind(func, c_p, std::placeholders::_1);
    
        std::function<void(Event&)> new_func = [=](Event& event){
            bind_f(static_cast<F>(event));
        };
        EventType type = E_class::GetStaticType();
        m_Events[type].push_back(new_func);
    }
    
    void dispatch(Event&);
    static EventDispatcher& getInstance() {
        static EventDispatcher instance;
        return instance;
    }
private:
    std::unordered_map<EventType, std::vector<std::function<void(Event&)>>> m_Events;
};
#endif /* Event_hpp */
