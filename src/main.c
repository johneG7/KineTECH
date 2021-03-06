#include <pebble.h>
#include <stdio.h>
#define TAP_NOT_DATA true

Window *myWindow;
TextLayer *titleText,*repCountText,*setCountText,*restCountText;
short unsigned int repMax = 0;
short unsigned int setMax = 5;
short unsigned int rest = 0;
short unsigned int reps = 1;
short unsigned int sets = 1;
short unsigned int timer = 0;
int state = 0; 
char restBuffer[20];
char repBuffer[20];
char setBuffer[20];
char timerBuffer[20];
bool movedDown = false;
bool movedUp = false;
static void general_gui_update(void);
static void on_play_gui(void);
static void wipe_screen(void);

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(state == 0){
    state = 1;
    general_gui_update();
  }else
  if(state == 1){
    state = 2;
    general_gui_update();
  }else
  if(state == 2){
    state = 3;
    general_gui_update();
  }else
  if(state == 3){
    state = 4;
    repMax = reps;
  text_layer_destroy(titleText);
   on_play_gui();
  }
  
  
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(state == 0){
    sets++;
    general_gui_update();
  }else
   if(state == 1){
    reps++;
    general_gui_update();
  }else
   if(state == 2){
    rest++;
    general_gui_update();
  }else 
    if(state == 3){
 //  on_play_gui();
  }
  
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
   if(state == 0 && sets > 0){
    sets--;
     general_gui_update();
   }else
   if(state == 1 && reps > 0){
    reps--;
     general_gui_update();
   }else
   if(state == 2 && rest > 0){
    rest--;
     general_gui_update();
   } else
   if(state == 3){
  // on_play_gui();
  }
 
}

static void long_down_click_handler(){
  
  titleText = text_layer_create(GRect(0, 0, 144, 168));
  text_layer_set_background_color(titleText, GColorClear);
  text_layer_set_text_color(titleText, GColorBlack);
  text_layer_set_font(titleText, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_alignment(titleText, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(titleText));
  text_layer_set_text(titleText, "Start");
  
  state = 0;
  general_gui_update();
}





void on_play_gui(){
  wipe_screen();
  setCountText = text_layer_create(GRect(0, 0, 144, 168));
  text_layer_set_background_color(setCountText, GColorClear);
  text_layer_set_text_color(setCountText, GColorBlack);
  text_layer_set_font(setCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(setCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(setCountText));
  snprintf(setBuffer, sizeof(setBuffer), "Sets:%d", sets);
  text_layer_set_text(setCountText, setBuffer);
  
  repCountText = text_layer_create(GRect(0, 50, 144, 168));
  text_layer_set_background_color(repCountText, GColorClear);
  text_layer_set_text_color(repCountText, GColorBlack);
  text_layer_set_font(repCountText, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_alignment(repCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(repCountText));
  snprintf(repBuffer, sizeof(setBuffer), "Reps:%d", reps);
  text_layer_set_text(repCountText, repBuffer);
  
  restCountText = text_layer_create(GRect(0, 110, 144, 168));
  text_layer_set_background_color(restCountText, GColorClear);
  text_layer_set_text_color(restCountText, GColorBlack);
  text_layer_set_font(restCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(restCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(restCountText));
  snprintf(restBuffer, sizeof(setBuffer), "Rest:%d", rest);
  text_layer_set_text(restCountText, restBuffer);
  
}

void general_gui_update(){
  wipe_screen();
  titleText = text_layer_create(GRect(0, 0, 144, 168));
  text_layer_set_background_color(titleText, GColorClear);
  text_layer_set_text_color(titleText, GColorBlack);
  text_layer_set_font(titleText, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_alignment(titleText, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(titleText));
  text_layer_set_text(titleText, "Start");
  
  setCountText = text_layer_create(GRect(0, 50, 144, 168));
  text_layer_set_background_color(setCountText, GColorClear);
  text_layer_set_text_color(setCountText, GColorBlack);
  text_layer_set_font(setCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(setCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(setCountText));
  snprintf(setBuffer, sizeof(setBuffer), "Sets:%d", sets);
  text_layer_set_text(setCountText, setBuffer);
  
  repCountText = text_layer_create(GRect(0, 80, 144, 168));
  text_layer_set_background_color(repCountText, GColorClear);
  text_layer_set_text_color(repCountText, GColorBlack);
  text_layer_set_font(repCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(repCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(repCountText));
  snprintf(repBuffer, sizeof(setBuffer), "Reps:%d", reps);
  text_layer_set_text(repCountText, repBuffer);
  
  restCountText = text_layer_create(GRect(0, 110, 144, 168));
  text_layer_set_background_color(restCountText, GColorClear);
  text_layer_set_text_color(restCountText, GColorBlack);
  text_layer_set_font(restCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(restCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(restCountText));
  snprintf(restBuffer, sizeof(setBuffer), "Rest:%d", rest);
  text_layer_set_text(restCountText, restBuffer);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 1000, long_down_click_handler, NULL);
}

void window_load(Window *myWindow){
  titleText = text_layer_create(GRect(0, 0, 144, 168));
  text_layer_set_background_color(titleText, GColorClear);
  text_layer_set_text_color(titleText, GColorBlack);
  text_layer_set_font(titleText, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_alignment(titleText, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(titleText));
  text_layer_set_text(titleText, "Start");
  
  setCountText = text_layer_create(GRect(0, 50, 144, 168));
  text_layer_set_background_color(setCountText, GColorClear);
  text_layer_set_text_color(setCountText, GColorBlack);
  text_layer_set_font(setCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(setCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(setCountText));
  snprintf(setBuffer, sizeof(setBuffer), "Sets:%d", sets);
  text_layer_set_text(setCountText, setBuffer);
  
  repCountText = text_layer_create(GRect(0, 80, 144, 168));
  text_layer_set_background_color(repCountText, GColorClear);
  text_layer_set_text_color(repCountText, GColorBlack);
  text_layer_set_font(repCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(repCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(repCountText));
  snprintf(repBuffer, sizeof(setBuffer), "Reps:%d", reps);
  text_layer_set_text(repCountText, repBuffer);
  
  restCountText = text_layer_create(GRect(0, 110, 144, 168));
  text_layer_set_background_color(restCountText, GColorClear);
  text_layer_set_text_color(restCountText, GColorBlack);
  text_layer_set_font(restCountText, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(restCountText, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(restCountText));
  snprintf(restBuffer, sizeof(setBuffer), "Rest:%d", rest);
  text_layer_set_text(restCountText, restBuffer);
  
}
static void wipe_screen(){
  if(state < 4){
text_layer_destroy(titleText);
  }
  text_layer_destroy(setCountText);
  text_layer_destroy(repCountText);
  text_layer_destroy(restCountText);
}
void window_unload(Window *myWindow){
  text_layer_destroy(titleText);
  text_layer_destroy(setCountText);
  text_layer_destroy(repCountText);
  text_layer_destroy(restCountText);
 
}

static void data_handler(AccelData *data, uint32_t num_samples) {
    if(state == 4){
    if( ((data[0].x + data[1].x)/2 ) > 200){
      movedUp = true;
    }
  
  if(movedUp && ((data[0].x + data[1].x)/2 ) < -200 ){
    if(reps == 0){
      reps = repMax;
      if(sets == 0){
        vibes_double_pulse();
        titleText = text_layer_create(GRect(0, 0, 144, 168));
        text_layer_set_background_color(titleText, GColorClear);
        text_layer_set_text_color(titleText, GColorBlack);
        text_layer_set_font(titleText, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
        text_layer_set_text_alignment(titleText, GTextAlignmentCenter);
        layer_add_child(window_get_root_layer(myWindow), text_layer_get_layer(titleText));
        text_layer_set_text(titleText, "Start");
  
        state = 0;
        general_gui_update();
      }
      else {
      sets--;
      //call delay
        
      }
    }
    else {
      reps--;
      if(reps == 0)
        vibes_long_pulse();
      movedUp = false;
      snprintf(repBuffer, sizeof(repBuffer), "Reps%d\n", reps );
      on_play_gui();
    }
  }
}
  
}

void init(){
  myWindow = window_create();
  window_set_click_config_provider(myWindow, click_config_provider);
  window_set_window_handlers(myWindow, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(myWindow, true);
  
 uint32_t num_samples = 2;
    accel_data_service_subscribe(num_samples,data_handler); 
 // accel_service_set_sampling_rate(ACCEL_SAMPLING_50HZ);
}

void deinit(){
   window_destroy(myWindow);
  
  if(TAP_NOT_DATA)
    accel_tap_service_unsubscribe();
}
  
int main(void){
  init();
  app_event_loop();
  deinit();
}