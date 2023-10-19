<template>
  <div class="home">
    <BlackSection>
      <h1 class="title">Welcome to the homepage </h1>
      <p class="p">{{ UserName }}</p>
    </BlackSection>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import BlackSection from '../components/general/BlackSection.vue'
import { useToast } from 'vue-toastification'
import { API } from '@/plugins/axios'

const activeUser = sessionStorage.getItem('activeuser')
console.log('activeUser:', activeUser)

export default defineComponent({
  name: 'HomePage',
  components: {
    BlackSection
  },
  data () {
    return {
      UserName: null,
      buttonClicked: false
    }
  },
  methods: {
    async getUsernameFromBackend () {
      try {
        const response = await API.get(`login?user=${activeUser}`)
        this.UserName = response.data.login
        if (activeUser) {
          await API.get(`updateUserActivity/${activeUser}/1`)
        }
      } catch (error) {
        const toast = useToast()
        toast.error('Failed to retrieve username') // Display a fail toast on error
      }
    }
  },
  created () {
    this.getUsernameFromBackend() // Call the method to retrieve the logged in username when the component is created
  }
})
</script>

<style scoped>

.title {
  margin: 4rem 0;
  font-size: 24px;
  text-align: center;
  color: #71beba;
  margin-top: 2rem; /* Add top margin */
}

.p {
  color: #71beba;
}

.home {
  display: flex;
  flex-direction: column;
  align-items: center; /* Align items horizontally in the center */
}

.home .custom-button {
  background-color: orange; /* change colour */
  padding: 15px 25px; /* Increase the padding to make the button bigger */
  font-size: 20px; /* Increase the font size of the button text */
  margin-top: 40px; /* Add margin-top to move the button down */
  font-weight: bold; /* Make the button text bold */
}

</style>
