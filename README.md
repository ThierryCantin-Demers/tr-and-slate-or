# tr-and-slate-or
Small c++ library to translate text directly in code. The library checks if a translation exists for the given string of text in the current language and returns it if it exists, otherwise it will send an api call to the DeepL or Google Translate API and store the result.

This library requires the nlohmann json library to work as the translations are stored in json file format.



The valid languages to translate to are determined by the ISO 639-1 standard. They are stored in the file translations/languages.json. I you want to add a custom language, you can do it by simply adding the language with its 2 letter code in the languages file and then adding the corresponding translation file.
