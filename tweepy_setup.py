import subprocess
import time
import tweepy

#add your api infos !! 

client = tweepy.Client(bearer_token, api_key, api_secret, access_token, access_token_secret)

auth = tweepy.OAuth1UserHandler(api_key, api_secret, access_token, access_token_secret) 
api = tweepy.API(auth)

#client.create_tweet(text="Hello Twitter")



def generate_image():
    #compiling the convert script
    subprocess.run(["python3", "convert.py"], check=True)

def post_image_to_twitter(image_path):
    # uploading the image  using API v1.1 
    media_id = api.media_upload(filename=image_path).media_id_string
    
    # now posting the image using API v2
    text = "Here's a new fractal image!"
    client.create_tweet(text=text, media_ids=[media_id])
    print("Tweeted!")


if __name__ == "__main__":
    while True:
        generate_image()  # generating a new fractal
        post_image_to_twitter("fractal.jpeg")  # path
        
        time.sleep(300)  # 5 min delay
