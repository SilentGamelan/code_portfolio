import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        # reads file line-by-line, ignores comments by testing first char of line, strips line-breaks from end
        # with ... as... will automatically close the file after the end of the loop (runtime context?)
        with open(positives, encoding='utf-8') as file_stream:
            self.pos_words = [line.rstrip('\n') for line in file_stream if line[0].isalpha()]

        with open(negatives, encoding='utf-8') as file_stream:
            self.neg_words = [line.rstrip('\n') for line in file_stream if line[0].isalpha()]


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        if not isinstance(text, str):
            # converts non-string value to string
            # I have forgotten why this is here.
            # ¯\_(ツ)_/¯
            text = str(text)

        score = 0
        tokenizer = nltk.tokenize.casual.TweetTokenizer()
        text = tokenizer.tokenize(text)

        # Haven't used elif/else as some words appear in both pos/neg lists - those words will now be counted as neutral (+1 then -1)
        for word in text:
            if word.lower() in self.pos_words:
                score += 1
            if word.lower() in self.neg_words:
                score -=1

        return score
