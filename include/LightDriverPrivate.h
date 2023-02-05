typedef struct LightDriverInterfaceStruct {
  void (*TurnOn)(LightDriver);
  void (*TurnOff)(LightDriver);
  void (*Destroy)(LightDriver);

} LightDriverInterfaceStruct;
