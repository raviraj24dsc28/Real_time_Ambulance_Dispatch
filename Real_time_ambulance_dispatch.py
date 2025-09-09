
%%writefile ambulance_app.py
import streamlit as st
import pandas as pd
import time
import random

st.set_page_config(page_title="🚑 Emergency Ambulance Dispatch System", layout="wide")

st.title("🚑 Emergency Ambulance Dispatch System")

# Sample hospital & ambulance data
ambulances = {
    "Ambulance 1": {"location": "City Center", "status": "Available"},
    "Ambulance 2": {"location": "North Zone", "status": "Available"},
    "Ambulance 3": {"location": "East Zone", "status": "Busy"},
}

hospitals = ["City Hospital", "Metro Hospital", "General Hospital"]

# User Input
st.sidebar.header("📍 Patient Emergency Request")
patient_name = st.sidebar.text_input("Patient Name")
location = st.sidebar.text_input("Emergency Location")
hospital = st.sidebar.selectbox("Select Hospital", hospitals)
priority = st.sidebar.radio("Emergency Priority", ["High", "Medium", "Low"])

if st.sidebar.button("🚨 Dispatch Ambulance"):
    available = [a for a, d in ambulances.items() if d["status"] == "Available"]
    if available:
        assigned = random.choice(available)
        ambulances[assigned]["status"] = "Busy"
        with st.spinner("Dispatching ambulance..."):
            time.sleep(2)
        st.success(f"✅ {assigned} dispatched to {patient_name} at {location} → {hospital} [Priority: {priority}]")
    else:
        st.error("❌ No ambulances available at the moment.")

st.subheader("🚑 Ambulance Status")
st.table(pd.DataFrame(ambulances).T)
