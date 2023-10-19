<template>
  <div class="profile">
    <div class="overlay"></div>
    <div v-if="userSpecified" class="content">
      <div class="left-section">
        <h1 class="title">Nickname: {{ nickName }}</h1>
        <div class="online-status green-text" v-if="this.user.currentStatus === 1"> <!-- Adjust the condition as needed -->
          <p>Status: Online</p>
        </div>
        <div class="online-status red-text" v-else-if="this.user.currentStatus === 2"> <!-- Adjust the condition as needed -->
          <p>Status: Offline</p>
        </div>
        <div class="online-status red-text" v-else-if="this.user.currentStatus === 3"> <!-- Adjust the condition as needed -->
          <p>Status: In a Game</p>
        </div>
        <img class="profile-picture" :src="profilePictureURL" alt="Profile Picture">
        <div class="button-container">
          <CustomButton v-if="privateProfile" class="custom-button" :handleClick="handleChangeButtonClick">Change Avatar</CustomButton>
          <CustomButton v-if="!privateProfile && !friendRequested && !areFriends && isLoggedIn && !isBlocked" class="custom-button" :handleClick="handleAddFriend">Add Friend</CustomButton>
          <CustomButton v-if="!privateProfile && !areFriends && isLoggedIn && !isBlocked" class="custom-button" :handleClick="handleBlock">Block User</CustomButton>
          <CustomButton v-if="!privateProfile && !areFriends && isLoggedIn && isBlocked && isBlocker" class="custom-button" :handleClick="handleUnblock">Unblock User</CustomButton>
          <CustomButton v-if="areFriends" class="custom-button" :handleClick="handleRemoveFriend">Remove Friend</CustomButton>
        </div>
        <div v-if="changePicRequest">
          <input type="file" ref="fileInput" @change="handleFileChange" />
          <CustomButton class="custom-button" :handleClick="handleUploadButtonClick">Upload</CustomButton>
        </div>
        <div>
          <CustomButton v-if="privateProfile" class="custom-button" :handleClick="handleEnableFa">Enable/Reset 2FA</CustomButton>
          <CustomButton v-if="privateProfile" class="custom-button" :handleClick="handleChangeName">Change Nickname</CustomButton>
        </div>
        <div v-if="showQRCode" style="background-color: white;">
          <!-- Display QR code using the 'qrcode.vue' component -->
          <qrcode :value="qrCodeData"></qrcode>
          <p>Scan with Google Authenticator<br>Then enter the 6 digits code below</p>
          <div>
            <input type="text" v-model="verificationCode" maxlength="6" />
            <CustomButton class="custom-button" :handleClick="verifyTwoFactorSetup">Submit</CustomButton>
          </div>
        </div>
      </div>
      <div class="right-section">
        <BlackSection>
          <div class="statistics">
            <h2 class="statistics-title">Statistics</h2>
            <div class="information">
              <div class="information-item">
                <h3 class="information-title">Rank: {{ playerItems.rank }}</h3>
              </div>
              <div class="information-item">
                <h3 class="information-title green-text">Wins: {{ playerItems.nbWin }}</h3>
              </div>
              <div class="information-item">
                <h3 class="information-title red-text">Losses: {{ playerItems.nbLoss }}</h3>
              </div>
            </div>
          </div>
        </BlackSection>
        <div class="spacing"></div>
        <BlackSection>
          <div class="match-history">
            <h2 class="statistics-title">Match History</h2>
            <div v-for="match in playerHistory" :key="match.matchId" class="match-item">
              <div class="match-result">
                <span class="match-outcome green-text" v-if="match.winnerId === otherUserId">WON AGAINST USERID:</span>
                <span class="match-outcome red-text" v-else>LOST AGAINST USERID:</span>
                <span class="match-opponent">{{ getOpponentId(match) }}</span>
              </div>
            </div>
          </div>
        </BlackSection>
      </div>
    </div>
    <div v-else class="content">
      <h1 class="title smaller">Whose profile would you like to see? </h1>
      <div class="input-group">
        <input id="otherUser" v-model.trim="otherUser" type="text" />
        <CustomButton class="custom-button" :handleClick="handleSearchButton">Search</CustomButton>
        <CustomButton v-if="isLoggedIn" class="custom-button" :handleClick="myProfileButton">My Profile</CustomButton>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import CustomButton from '../components/general/CustomButton.vue'
import BlackSection from '../components/general/BlackSection.vue'
import qrcode from 'qrcode.vue'
import { API } from '@/plugins/axios'
import { useToast } from 'vue-toastification'

const siteIP = process.env.VUE_APP_SITE_IP
const apiKey = process.env.VUE_APP_SECRET

interface MatchHistoryItem {
  matchId: number;
  playerOneId: number;
  playerTwoId: number;
  winnerId: number;
}

export default defineComponent({
  name: 'ProfilePage',
  components: {
    BlackSection,
    CustomButton,
    qrcode
  },
  data () {
    return {
      buttonClicked: false,
      activeUser: sessionStorage.getItem('activeuser') || '',
      nickName: '',
      otherUser: '',
      otherUserId: -1,
      secretKey: '',
      showQRCode: false,
      privateProfile: false,
      userSpecified: false,
      isLoggedIn: false,
      changePicRequest: false,
      areFriends: false,
      isBlocked: false,
      isBlocker: false,
      friendRequested: false,
      selectedFile: null as File | null,
      historyUpdated: false,
      playerItems: {
        nbWin: 0,
        nbLoss: 0,
        rank: ''
      },
      user: {
        id: 0,
        login: '',
        currentStatus: 0
      },
      match: {
        matchId: 0,
        playerOneId: 0,
        playerTwoId: 0,
        winnerId: 0
      },
      verificationCode: '',
      playerHistory: [] as MatchHistoryItem[]
    }
  },
  computed: {
    qrCodeData (): string {
      return `otpauth://totp/${this.activeUser}?secret=${this.secretKey}&issuer=Sonic`
    },
    profilePictureURL (): string {
      return `http://${siteIP}:3000/${apiKey}/profilepic?user=${this.otherUser}`
    }
  },
  methods: {
    handleChangeButtonClick () {
      console.log('Change button clicked!')
      this.changePicRequest = true
      this.buttonClicked = false
      // Define the behavior for the 'Change' button click
    },
    handleFileChange (event: Event) {
      const inputElement = event.target as HTMLInputElement
      if (inputElement.files && inputElement.files.length > 0) {
        this.selectedFile = inputElement.files[0]
      }
    },
    async handleUploadButtonClick () {
      const toast = useToast()
      if (!this.selectedFile) {
        toast.error('No File Selected')
        return
      }

      const formData = new FormData()
      formData.append('username', this.activeUser)
      formData.append('profilePicture', this.selectedFile)
      try {
        const response = await API.post('profilepicchange', formData, {
          headers: {
            'Content-Type': 'multipart/form-data'
          }
        })

        const status = response.data
        if (status) {
          window.location.reload()
        } else {
          toast.error('Profile Picture Change Failed')
        }
      } catch (error) {
        console.error('Failed to upload profile picture:', error)
      }
    },
    handleAddFriend () {
      console.log('Friend add button clicked!')
      this.friendRequest()
      this.buttonClicked = false
    },
    handleRemoveFriend () {
      console.log('Friend add button clicked!')
      const confirmation = window.confirm('Are you sure you want to remove this friend?')
      if (confirmation) {
        this.friendRemoval()
      }
      this.buttonClicked = false
    },
    handleBlock () {
      console.log('Block button clicked!')
      const confirmation = window.confirm('Are you sure you want to block this user?')
      if (confirmation && this.areFriends) {
        this.friendRemoval()
      }
      this.blockUser()
      this.buttonClicked = false
    },
    handleUnblock () {
      console.log('Unblock button clicked!')
      const confirmation = window.confirm('Are you sure you want to unblock this user?')
      if (confirmation) {
        this.unblockUser()
      }
      this.buttonClicked = false
    },
    handleEnableFa () {
      console.log('Enable 2FA button clicked!')
      const confirmation = window.confirm('Are you sure? If you have an existing key, this will overwrite it and cannot be undone.')
      if (confirmation) {
        this.showQRCode = true
        this.initiateTwoFactorSetup()
      }
      this.buttonClicked = false
    },
    async handleChangeName () {
      console.log('ChangeName button clicked!')
      const inputNewName = window.prompt('Enter your new nickname:')
      const toast = useToast()
      if (inputNewName) {
        try {
          const response = await API.post('changename', {
            username: this.activeUser,
            newNickName: inputNewName
          })

          const status = response.data
          if (status) {
            window.location.reload()
          } else {
            toast.error('Nickname Change Failed')
          }
        } catch (error) {
          console.error('Error verifying two-factor setup:', error)
        }
        this.buttonClicked = false
      } else {
        toast.error('No Name Entered')
      }
    },
    handleSearchButton () {
      console.log('Search button clicked!')
      this.searchUser()
      this.buttonClicked = false
    },
    myProfileButton () {
      console.log('My Profile button clicked!')
      window.location.href = `http://${siteIP}/profile?user=${this.activeUser}`
      this.buttonClicked = false
    },
    countWinLose () {
      const nbWin = this.playerHistory.filter((ph) => ph.winnerId === this.user.id).length
      const nbLoss = this.playerHistory.filter((ph) => ph.winnerId !== this.user.id).length
      this.playerItems.nbWin = nbWin
      this.playerItems.nbLoss = nbLoss
    },
    formatDate (dateString: string) {
      const date = new Date(dateString)
      return date.toLocaleDateString() // You can use any date formatting method here based on your preferences
    },
    async initiateTwoFactorSetup () {
      // Send an API call to the backend to initiate 2FA setup
      try {
        const response = await API.get(`twofa?user=${this.activeUser}`, {
          headers: {
            'Content-Type': 'application/json'
          }
        })

        this.secretKey = response.data.secretKey
      } catch (error) {
        console.error('Error initiating 2FA setup:', error)
      }
    },
    async searchUser () {
      try {
        const response = await API.get(`login?user=${this.otherUser}`, {
          headers: {
            'Content-Type': 'application/json'
          }
        })

        const name = response.data.login
        this.nickName = response.data.nickname
        if (!name) {
          this.otherUser = ''
          const toast = useToast()
          toast.error('Username Not Found')
        } else {
          window.location.href = `http://${siteIP}/profile?user=${this.otherUser}`
        }
      } catch (error) {
        console.error('Search Button Error:', error)
      }
    },
    async verifyTwoFactorSetup () {
      try {
        const response = await API.post('twofa', {
          username: this.activeUser,
          verificationCode: this.verificationCode
        })

        const status = response.data
        const toast = useToast()
        if (status) {
          toast.success('2FA enabled!')
        } else {
          toast.error('2FA Setup Failed')
        }
      } catch (error) {
        console.error('Error verifying two-factor setup:', error)
      }
    },
    async parseUserinfo () {
      const urlParams = new URLSearchParams(window.location.search)
      const username = urlParams.get('user')

      if (username) {
        this.userSpecified = true
        this.otherUser = username
        if (username === this.activeUser) {
          this.privateProfile = true
        }
      }
      if (this.activeUser) {
        this.isLoggedIn = true
        await API.get(`updateUserActivity/${this.activeUser}/1`)
        try {
          const response = await API.get(`login?user=${this.otherUser}`)
          this.nickName = response.data.nickname
          this.otherUserId = Number(response.data.id)
          this.user.currentStatus = response.data.currentStatus
        } catch (error) {
          console.error('Internal Error:', error)
        }
      }
      const idOne = await this.getUserId(this.activeUser)
      const idTwo = await this.getUserId(this.otherUser)

      if (idOne && idTwo) {
        try {
          const response = await API.get(`friend/are-friends?idOne=${idOne}&idTwo=${idTwo}`)
          if (response.data) {
            this.areFriends = true
          }

          const blockCheck = await API.get(`block/are-blocked?idOne=${idOne}&idTwo=${idTwo}`)
          if (blockCheck.data !== 0) {
            this.isBlocked = true
            if (blockCheck.data === idOne) {
              this.isBlocker = true
            }
          }
        } catch (error) {
          console.error('Error fetching user ID:', error)
        }

        try {
          const response = await API.get(`matches/${idTwo}`)
          this.playerHistory = response.data
          this.playerItems.nbWin = this.playerHistory.filter(match => match.winnerId === this.otherUserId).length
          this.playerItems.nbLoss = this.playerHistory.filter(match => match.winnerId !== this.otherUserId).length
          if (this.playerItems.nbWin - this.playerItems.nbLoss > 0) {
            this.playerItems.rank = 'Silver'
          } else if (this.playerItems.nbWin - this.playerItems.nbLoss > 5) {
            this.playerItems.rank = 'Gold'
          } else {
            this.playerItems.rank = 'Bronze'
          }
        } catch (error) {
          console.error('Error fetching match history:', error)
        }
      }
    },
    async friendRequest () {
      const idOne = await this.getUserId(this.activeUser)
      const idTwo = await this.getUserId(this.otherUser)
      const toast = useToast()

      try {
        const response = await API.post('friend/edit-friend', {
          userId: idOne,
          friendId: idTwo,
          action: 2
        })

        if (response.status === 201) {
          this.friendRequested = true
          toast.success('Friend Requested Sent / Already Sent')
        }
      } catch (error) {
        this.friendRequested = true
        toast.success('Friend Requested Sent / Already Sent')
      }
    },
    async friendRemoval () {
      const idOne = await this.getUserId(this.activeUser)
      const idTwo = await this.getUserId(this.otherUser)
      const toast = useToast()

      try {
        const response = await API.post('friend/edit-friend', {
          userId: idOne,
          friendId: idTwo,
          action: 1
        })

        if (response.data) {
          toast.success('Friend Removed!')
        } else {
          toast.error('Friend removal failed')
        }
      } catch (error) {
        console.error('Error sending friend request:', error)
      }
    },
    async blockUser () {
      const idOne = await this.getUserId(this.activeUser)
      const idTwo = await this.getUserId(this.otherUser)
      const toast = useToast()

      try {
        const response = await API.post('block/block', {
          userId: idOne,
          blockId: idTwo
        })

        if (response.status === 201) {
          toast.success('User Blocked')
        } else {
          toast.error('User block failed')
        }
      } catch (error) {
        console.error('Error:', error)
      }
    },
    async unblockUser () {
      const idOne = await this.getUserId(this.activeUser)
      const idTwo = await this.getUserId(this.otherUser)
      const toast = useToast()

      try {
        const response = await API.post('block/unblock', {
          userId: idOne,
          blockId: idTwo
        })

        if (response.status === 201) {
          toast.success('User Unblocked')
        } else {
          toast.error('User unblock failed')
        }
      } catch (error) {
        console.error('Error:', error)
      }
    },
    async getUserId (username: string) {
      try {
        const response = await API.get(`login?user=${username}`)
        return response.data.id
      } catch (error) {
        console.error('Error fetching user ID:', error)
        throw error
      }
    },
    getOpponentId (match: {
      playerOneId: number;
      playerTwoId: number;
    }): number {
      if (match.playerOneId === this.otherUserId) {
        return match.playerTwoId
      } else {
        return match.playerOneId
      }
    }
  },
  created () {
    this.parseUserinfo()
  }
})
</script>

<style scoped>
.profile {
  position: relative;
}

.overlay {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: black; /* Set the background color to black */
  opacity: 0.5; /* Adjust the opacity as needed */
  z-index: 1; /* Ensure the overlay appears above other elements */
}

.content {
  position: relative;
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 20px;
  z-index: 2; /* Ensure the content appears above the overlay */
}

.left-section {
  display: flex;
  flex-direction: column;
  align-items: center; /* Align the buttons to the center horizontally */
}

.button-container {
  display: flex;
  justify-content: center; /* Center the buttons horizontally */
}

.custom-button {
  margin: 5px; /* Add margin to create space between buttons */
  width: 100px; /* Adjust the width as needed */
}

.profile-picture {
  width: 150px; /* Adjust the width as needed */
  height: 150px; /* Adjust the height as needed */
  object-fit: cover; /* Ensure the image maintains its aspect ratio */
  border-radius: 50%; /* Make the image circular */
  margin-bottom: 1rem; /* Add margin-bottom to create space below the profile picture */
}

.right-section {
  flex-grow: 1;
  margin-left: 20px; /* Add margin to create space between sections */
}

.title {
  margin: 0;
  font-size: 24px;
  text-align: center;
  color: #71beba;
  margin-bottom: 1rem; /* Adjust the margin-bottom as needed */
}

.profile .custom-button {
  margin-bottom: 10px; /* Add margin-bottom to create space between buttons */
}

.statistics-title {
  margin-top: 0;
  font-size: 20px;
  color: #71beba;
  font-family: Arial, sans-serif;
}

.information {
  margin-top: 10px; /* Adjust the margin-top as needed */
}

.information-item {
  margin-bottom: 1px; /* Adjust the margin-bottom as needed */
}

.information-title {
  margin: 0;
  font-size: 12px;
  color: white; /* Set the color for the information title */
}

.green-text {
  color: green; /* Set the color for the "Wins" title */
}

.red-text {
  color: red; /* Set the color for the "Losses" title */
}
.match-outcome {
  font-size: 10px; /* Adjust the font size for the "WON/LOST AGAINST" text */
  margin-right: 5px; /* Add a small margin to the right of the text */
}
.match-opponent{
  font-size: 10px; /* Adjust the font size for the "WON/LOST AGAINST" text */
  margin-right: 5px; /* Add a small margin to the right of the text */
}
.match-date {
  font-size: 10px; /* Adjust the font size for the "WON/LOST AGAINST" text */
  margin-right: 5px; /* Add a small margin to the right of the text */
}
.spacing {
  margin-bottom: 1rem;
}

.online-status {
  font-size: 25px; /* Adjust the font size for the online status text */
  margin-right: 5px; /* Add a small margin to the right of the text */
}
</style>
