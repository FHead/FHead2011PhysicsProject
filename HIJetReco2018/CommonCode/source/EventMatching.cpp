#include <map>

#include "include/Messenger.h"
#include "include/EventMatching.h"

EventCoordinate::EventCoordinate()
   : Run(0), Event(0), Lumi(0)
{
}

EventCoordinate::EventCoordinate(long long run, long long event, long long lumi)
   : Run(run), Event(event), Lumi(lumi)
{
}
   
EventCoordinate::EventCoordinate(TriggerTreeMessenger &M)
   : Run(M.Run), Event(M.Event), Lumi(M.Lumi)
{
}

EventCoordinate::EventCoordinate(HiEventTreeMessenger &M)
   : Run(M.Run), Event(M.Event), Lumi(M.Lumi)
{
}

bool EventCoordinate::operator <(const EventCoordinate &other) const
{
   if(Run < other.Run)   return true;
   if(Run > other.Run)   return false;
   if(Event < other.Event)   return true;
   if(Event > other.Event)   return false;
   if(Lumi < other.Lumi)   return true;
   if(Lumi > other.Lumi)   return false;
   return false;
}

template<class T>
std::map<EventCoordinate, int> BuildMap(T &M, bool Empty)
{
   std::map<EventCoordinate, int> Location;

   int EntryCount = M.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      M.GetEntry(i);

      if(Empty == true)
         Location.insert(std::pair<EventCoordinate, int>(EventCoordinate(M), -1));
      else
         Location.insert(std::pair<EventCoordinate, int>(EventCoordinate(M), i));
   }

   return Location;
}

template<class T>
std::map<EventCoordinate, int> &BuildMap(T &M, std::map<EventCoordinate, int> &Location)
{
   int EntryCount = M.Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      M.GetEntry(i);

      EventCoordinate E(M);
      if(Location.find(E) == Location.end())
         continue;

      Location[E] = i;
   }

   return Location;
}

template std::map<EventCoordinate, int> BuildMap<TriggerTreeMessenger>(TriggerTreeMessenger &M, bool Empty);
template std::map<EventCoordinate, int> BuildMap<HiEventTreeMessenger>(HiEventTreeMessenger &M, bool Empty);
template std::map<EventCoordinate, int> &BuildMap<TriggerTreeMessenger>(TriggerTreeMessenger &M, std::map<EventCoordinate, int> &Location);
template std::map<EventCoordinate, int> &BuildMap<HiEventTreeMessenger>(HiEventTreeMessenger &M, std::map<EventCoordinate, int> &Location);


