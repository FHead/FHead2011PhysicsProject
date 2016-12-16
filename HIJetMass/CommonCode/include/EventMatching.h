#include <map>

class TriggerTreeMessenger;
class HiEventTreeMessenger;

class EventCoordinate
{
public:
   long long Run;
   long long Event;
   long long Lumi;
public:
   EventCoordinate();
   EventCoordinate(long long run, long long event, long long lumi);
   EventCoordinate(TriggerTreeMessenger &M);
   EventCoordinate(HiEventTreeMessenger &M);
   bool operator <(const EventCoordinate &other) const;
};

template<class T>
std::map<EventCoordinate, int> BuildMap(T &M, bool Empty = true);
template<class T>
std::map<EventCoordinate, int> &BuildMap(T &M, std::map<EventCoordinate, int> &Location);



