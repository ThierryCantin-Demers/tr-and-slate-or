# tr-and-slate-or
Small c++ library to translate text directly in code. The library checks if a translation exists for the given string of text in the current language and returns it if it exists, otherwise it will send an api call to the DeepL API and store the result.

This library requires the nlohmann json library to work as the translations are stored in json file format.
