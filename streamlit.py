from pyngrok import ngrok

# Start Streamlit app
!streamlit run ambulance_app.py &

# Expose the port 8501
public_url = ngrok.connect(8501)
print("🌍 Your Streamlit App URL:", public_url)
