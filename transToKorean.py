from googletrans import Translator
translator = Translator()

def translate(engSentence):
    result = translator.translate(engSentence, dest="ko")
    return result.text
