class ItemsController < ApplicationController
   before_action :find_item, only: [:show, :edit, :update, :destroy]
   
    def index
        @items = Item.all
    end
    
    def show
    end

    def new
        @item = Item.new
    end

    def create
        @item = Item.new(params.require(:item).permit(:title, :description))
        if @item.save
            redirect_to root_path
        else
            render 'new'
        end
        
    end

    def edit 
    end

    def update
        if @item.update(params.require(:item).permit(:title, :description))
            redirect_to item_path(@item)
        else
            render 'edit'
        end
    end

    def complete
        @item = Item.find(params[:id])
        @item.update_attribute(:completed_at, Time.now)
        redirect_to root_path
    end

    def destroy
        @item.destroy
        redirect_to root_path
    end

        private
            def find_item
                @item = Item.find(params[:id]) #finds the item by the id

            end         
end
