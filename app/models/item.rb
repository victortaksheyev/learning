class Item < ApplicationRecord
    def completed?
        !completed_at.blank? #not null
    end
end
